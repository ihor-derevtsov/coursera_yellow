#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

auto get_char(char c) { return c; }
auto get_char(string const& s) { return s[0]; }


template <typename RandomIt> 
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
 //return  equal_range(range_begin, range_end, prefix,[](const char& pre, const string& str) {return str[0] < pre; });       //Непонятно почему не работает
 return  equal_range(range_begin, range_end, prefix, [](auto const& l, auto const& r) { return get_char(l) < get_char(r); });//непонятно почему работает 
}


/*
Your output:
0 0 2 2 3 3 

Correct output:
0 2 2 2 3 3
*/

int main() {
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    cout << (m_result.first - begin(sorted_strings)) << " " <<
        (m_result.second - begin(sorted_strings)) << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}
/* moscow murmansk
2 2
3 3
*/