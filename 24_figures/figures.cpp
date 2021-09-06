#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

/* базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area */
class Figure {
public:
    Figure(const string& s) : type_(s) {}
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
protected:
    string type_;
};

/* классы Triangle, Rect и Circle, которые являются наследниками класса Figure 
и переопределяют его виртуальные методы */
class Triangle : public Figure {
public:
    Triangle(const string& s, 
            const int& a, 
            const int& b, 
            const int& c) : Figure(s) {
                perimeter_ = a + b + c;
                double half_p = perimeter_/2;
                area_ = sqrt((half_p) * (half_p - a) * (half_p - b) * (half_p - c));
    }

    string Name() const override {
        return type_;
    }
    double Perimeter() const override {
        return perimeter_;
    }
    double Area() const override {
        return area_;
    }
private:
    double perimeter_;
    double area_;
};

class Rect : public Figure {
public:
    Rect(const string& s,
        const int& a,
        const int& b) : Figure(s) {
        perimeter_ = 2 * (a + b);
        area_ = a * b;
    }
    string Name() const override {
        return type_;
    }
    double Perimeter() const override {
        return perimeter_;
    }
    double Area() const override {
        return area_;
    }
private:
    double perimeter_;
    double area_;
};

class Circle : public Figure {
public:
    Circle(const string& s, const int& r) : Figure(s) {
        perimeter_ = 2 * PI * r;
        area_ = PI * r * r;
    }
    string Name() const override {
        return type_;
    }
    double Perimeter() const override {
        return perimeter_;
    }
    double Area() const override {
        return area_;
    }
private:
    double perimeter_;
    double area_;
    const double PI = 3.14; 
};


/* функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, 
shared_ptr<Triangle> или shared_ptr<Circle> */
shared_ptr<Figure> CreateFigure(istream& stream) {
    string name;
    int a, b, c, r;
    stream >> name;
    if (name == "RECT") { 
        stream >> a >> b;
        return make_shared<Rect>(name, a, b); 
    }
    else if (name == "TRIANGLE") { 
        stream >> a >> b >> c;
        return make_shared<Triangle>(name, a, b, c); 
    }
    else { 
        stream >> r;
        return make_shared<Circle>(name, r); 
    }
}



int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
        // Пропускаем "лишние" ведущие пробелы.
        // Подробнее об std::ws можно узнать здесь:
        // https://en.cppreference.com/w/cpp/io/manip/ws
        is >> ws;
        figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
        for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
                << current_figure->Name() << " "
                << current_figure->Perimeter() << " "
                << current_figure->Area() << endl;
        }
    }
    }
    return 0;
}

/*
ADD RECT 2 3
ADD TRIANGLE 3 4 5
ADD RECT 10 20
ADD CIRCLE 5
PRINT

RECT 10.000 6.000
TRIANGLE 12.000 6.000
RECT 60.000 200.000
CIRCLE 31.400 78.500
*/