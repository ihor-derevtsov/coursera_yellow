#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& s, const string& type) : name_(s), type_(type) { }
    virtual void Walk(const string& destination) const = 0;

    const string name_;
    const string type_;
};

class Student : public Human {
public:

    Student(const string& name, const string& favouriteSong) : 
        Human(name, "Student"), FavouriteSong(favouriteSong) {
    }

    void Learn() {
        cout << "Student: " << name_ << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Student: " << name_ << " walks to: " << destination << endl;
        cout << "Student: " << name_ << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << name_ << " sings a song: " << FavouriteSong << endl;
    }

    const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : 
        Human(name, "Teacher"), Subject(subject) {
    }

    void Teach() {
        cout << "Teacher: " << name_ << " teaches: " << Subject << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Teacher: " << name_ << " walks to: " << destination << endl;
    }

    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(string name) : Human(name, "Policeman") {
    }

    void Check(const Human& human) {
        cout << "Policeman: " << name_ << " checks " << human.type_ << ". " 
        << human.type_ << "'s name is: " << human.name_ << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Policeman: " << name_ << " walks to: " << destination << endl;
    }
};

void VisitPlaces(const Human& human, const vector<string>& places) {
    for (const auto& p : places) {
        human.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
