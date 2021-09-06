#include <iostream>
#include <vector>
#include <map>


using namespace std;

int main() {

    uint64_t N, R, W, H, D;
    uint64_t M;
    uint64_t result{0};
    vector<uint64_t> weights;
    cin >> N >> R;
    for (auto i{0}; i < N; i++) {
        cin >> W >> H >> D;
        M = W*H*D*R;
        weights.push_back(M);
    }
    for (const auto& item : weights) { result += item; }
    cout << result;
    return 0; 
}