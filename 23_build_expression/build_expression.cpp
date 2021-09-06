#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <sstream>

using namespace std;

struct Operation {
    int number;
    char code;
};

ostream& operator<<(ostream& os, const Operation& operation) {
    os << ' ' << operation.code << ' ' << operation.number << ')';
    return os;
}


int main() {
    deque<Operation> operations;
    Operation my_operation;
    stringstream expression;
    int n;
    cin >> my_operation.number >> n;
    if (n == 0) { cout << my_operation.number; return 0; }
    string braces(n, '(');
    expression << braces << my_operation.number << ')';
    for (int i{0}; i < n; ++i) {
        cin >> my_operation.code >> my_operation.number;
        operations.push_back(my_operation);
    }
    
    // for (const auto& item : operations) {
    //     cout << item.code << item.number << ' ';
    // }
    
    for (const auto& item : operations) {
        expression << item;
    }
    string result = expression.str();
    result.pop_back();
    cout << result << endl;
    
    return 0;
}
/*
8
3
* 3
- 6
/ 1
*/