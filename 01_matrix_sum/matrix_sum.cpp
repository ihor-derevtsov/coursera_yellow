#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
class Matrix {
public:
    Matrix() {
        num_rows = 0;
        num_cols = 0;
    }
    
    Matrix(const int rows, const int cols) {
        Reset(rows, cols);
    }

    void Reset(const int rows, const int cols) {
        if (rows > 0 && cols > 0) {
            num_rows = rows;
            num_cols = cols;
            data.assign(num_rows, vector<int>(num_cols));
        } else if (rows == 0 || cols == 0) {
            num_rows = 0;
            num_cols = 0;
            data.clear();
        } else { throw out_of_range("Rows / cols can't be less than 0."); }
    }

    int At(const int row, const int col) const {
        return data.at(row).at(col);
    }

    int& At(const int row, const int col) {
        return data.at(row).at(col);
    }

    int GetNumRows() const {
        return num_rows;
    }

    int GetNumColumns() const {
        return num_cols;
    }

private:
    int num_rows;
    int num_cols;
    vector< vector<int> > data;
};


// * оператор ввода для класса Matrix из потока istream
istream& operator>>(istream& stream, Matrix& object) {
    int rows, cols;
    stream >> rows >> cols;
    object.Reset(rows, cols);
    for (auto i{0}; i < rows; ++i) {
        for (auto j{0}; j < cols; ++j) {
            stream >> object.At(i, j);
        }
    }
    return stream;
}

// * оператор вывода класса Matrix в поток ostream
ostream& operator<<(ostream& stream, const Matrix& object) {
    stream << object.GetNumRows() << ' ' << object.GetNumColumns() << endl;
    for (auto i{0}; i < object.GetNumRows(); ++i) {
        for (auto j{0}; j < object.GetNumColumns(); ++j) {
            if (j > 0) { stream << ' '; }
            stream << object.At(i, j);
        }
        stream << endl;
    }
    return stream;
}

// * оператор проверки на равенство двух объектов класса Matrix
bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.GetNumColumns() != rhs.GetNumColumns()) { return false; }
    if (rhs.GetNumRows() != lhs.GetNumRows()) { return false; }
    for (auto i{0}; i < lhs.GetNumRows(); ++i) {
        for (auto j{0}; j < lhs.GetNumColumns(); ++j) {
            if (lhs.At(i, j) != rhs.At(i, j)) { return false; }
        }
    }
    return true;
}

// * оператор сложения двух объектов класса Matrix
Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.GetNumRows() != rhs.GetNumRows()) { throw invalid_argument("Mismatched number of rows"); }
    if (lhs.GetNumColumns() != rhs.GetNumColumns()) { throw invalid_argument("Mismatched number of columns"); }
    Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
    for (auto i{0}; i < lhs.GetNumRows(); ++i) {
        for (auto j{0}; j < lhs.GetNumColumns(); ++j) {
            result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return result;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}
