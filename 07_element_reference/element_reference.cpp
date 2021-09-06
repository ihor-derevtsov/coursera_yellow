#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

template<typename key, typename value> value& GetRefStrict(map<key, value>& m, key k);

template<typename key, typename value>
value& GetRefStrict(map<key, value>& m, key k) {
    if (m.count(k) != 0) { return m.at(k); }
    else { throw runtime_error("Error"); }
}


int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
    return 0;
}
