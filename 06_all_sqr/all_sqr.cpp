#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

template<typename T> T Sqr(const T& item);
template<typename T> vector<T> operator*(const vector<T>& v1, const vector<T>& v2);
template<typename key, typename value> pair<key, value> operator*(const pair<key,value>& p1, const pair<key,value>& p2);
template<typename key, typename value> map<key, value> operator*(const map<key, value>& m1, const map<key, value>& m2);

template<typename T>
T Sqr(const T& item) {
    return item * item;
}

template<typename T>
vector<T> operator*(const vector<T>& v1, const vector<T>& v2) {
    vector<T> result{};
    for (int i{0}; i < v1.size(); ++i) {
        result.push_back(v1[i]*v2[i]);
    }
    return result;
}

template<typename key, typename value>
pair<key, value> operator*(const pair<key,value>& p1, const pair<key,value>& p2) {
    return {(p1.first * p2.first), (p1.second * p2.second)};

}

template<typename key, typename value>
map<key, value> operator*(const map<key, value>& m1, const map<key, value>& m2) {
    map<key,value> result{};
    for (const auto& pair : m1) {
        result[pair.first] = Sqr(pair.second);
    }
    return result;
}




int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}
/*
vector: 1 4 9
map of pairs:
4 4 4
7 16 9
*/