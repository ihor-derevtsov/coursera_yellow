#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    auto it = find_if(elements.begin(), elements.end(), [border] (const T& item) { return (item > border); });
    vector<T> result(it, elements.end());
    return result;
}


int main() {
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
    }
    cout << endl;

    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}

