#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers);


int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}

void PrintVectorPart(const vector<int>& numbers) {
    auto it = find_if(numbers.begin(), numbers.end(), [] (const int& i) { return (i < 0); });
    for (; it != numbers.begin(); ) {
        cout << (*--it) << ' ';
    }
}
