#include <iostream>
#include <vector>
#include <map>


using namespace std;

int main() {
    int N;
    int64_t sum{0};
    vector<int> t;
    cin >> N;
    for (auto i{0}; i < N; ++i) {
        int c;
        cin >> c;
        t.push_back(c);
        sum += c;
    }
    int avg = sum / N;
    map<int, int> result;
    
    for (int i{0}; i < static_cast<int>(t.size()); ++i) {
        if (t[i] > avg) { result[i] = t[i]; }
    }

    cout << result.size() << endl;
    for (const auto& pair : result) { cout << pair.first << ' '; }
    

    return 0; 
}