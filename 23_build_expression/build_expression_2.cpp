#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <sstream>
#include <map>


using namespace std;

struct Operation {
    int number{};
    char code = '$';
    string additional{};
};

ostream& operator<<(ostream& stream, const Operation& operation) {
    if (operation.code == '$') { stream << operation.number; }
    else { stream << ' ' << operation.code << ' ' << operation.number; }
    if (!operation.additional.empty()) { stream << operation.additional; }
    return stream;
}

void MakeExpression() {
    const map<char, int> priority_of_operator{ {'/', 2}, {'*', 2}, {'-', 1}, {'+', 1} };
    deque<Operation> operations;
    Operation my_operation;
    stringstream expression;
    /* Считываю исходное значение и n и добавляю в контейнер с операциями */
    int n;
    cin >> my_operation.number >> n;
    if (n == 0) { cout << my_operation.number; exit(0); }
    operations.push_back(my_operation);
    /* Добавляю остальные n операций */
    for (int i{0}; i < n; ++i) {
        cin >> my_operation.code >> my_operation.number;
        operations.push_back(my_operation);
    }
    /* Сравниваю приоритеты последующей операции с предыдущей, ставлю скобки (тут наверное ошибочка) */
    int counter{0};
    for (int i{1}; i < operations.size(); ++i) {
        if (operations[i-1].code != '$') {
            if (priority_of_operator.at(operations[i].code) > priority_of_operator.at(operations[i-1].code) &&
                operations.size() != 2) {
                    ++counter;
                    operations[i-1].additional = ")";
                }
        }
    }
    /* Ставлю необходимые скобки в начало */
    if (operations.size() != 2) {
    string braces(counter, '(');
    expression << braces;
    }
    /* Вывожу операции */
    for (const auto& item : operations) {
        expression << item;
    }
    /* Вывожу выражение */
    cout << expression.str() << endl;
    
}


int main() {
    MakeExpression();
    return 0;
}

/*
8
3
* -3
- 6
* -1
(8 * -3 - 6) * -1 OK

8
3
* 3
- 6
/ 1
(8 * 3 - 6) / 1 OK

8
3
* 3
* 6
* 1

8 
3 
- -3 
* 6 
* 1
(8 - -3) * 6 * 1 OK

8
3
/3
/ 6
/ 111
8 / 3 / 6 / 111 OK

1
7
+ 1 - 2 + 3 * 4 / 5 * 6 * 7
((1 + 1 - 2 + 3) * 4) / 5 * 6 * 7 OK

- 5
2
*3
/5
(-5 * 3) / 5 НЕ OK, но такое и не нужно рассматривать, насколько я понял

-3 2
*-2
+ 1
-3 * -2 + 1 OK

8
2
/5
*2
8 / 5 * 2 OK

-2 3
*2
+3
*1
(-2 * 2 + 3) * 1

6
3
* -1
/ -1
+ -3
(6 * -1) / -1 + -3 МОЙ

6 * -1 / -1 + -3 ПРАВИЛЬНЫЙ

*/