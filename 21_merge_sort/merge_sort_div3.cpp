#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 3) { return; }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    vector<typename RandomIt::value_type> temp;
    
    auto border = elements.begin() + elements.size()/3;
    auto border2 = border + elements.size()/3;
    MergeSort(elements.begin(), border);
    MergeSort(border, border2);
    MergeSort(border2, elements.end());

    merge(elements.begin(), border, border, border2, back_inserter(temp));
    merge(temp.begin(), temp.end(), border2, elements.end(), range_begin);
}




int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
    cout << x << " ";
    }
    cout << endl;
    return 0;
}