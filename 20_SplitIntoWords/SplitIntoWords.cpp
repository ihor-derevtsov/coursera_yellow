#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> res;
    
    auto iter = s.begin();
    auto border = find(s.begin(), s.end(), ' ');

    while(border != s.end()) {
        string ss(iter, border);
        res.push_back(ss);
        iter = border;
        border = find(++iter, s.end(), ' ');
    }
    string sss(iter, s.end());
    res.push_back(sss);
    return res;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
    cout << "/";
    }
    cout << *it;
    }
    cout << endl;
    return 0;
}