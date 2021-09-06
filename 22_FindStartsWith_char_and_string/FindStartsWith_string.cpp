#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool lower_comparator(const std::string& left, const std::string& right)
{

    if (right.size() > left.size())
    {
		return left < right;
    }

	const size_t size = std::min(right.size(), left.size());

	return left.substr(0, size) < right.substr(0, size);
}


bool upper_comparator(const std::string& left, const std::string& right)
{

	if (left.size() > right.size())
	{
		return left < right;
	}

	const size_t size = std::min(right.size(), left.size());

	return left.substr(0, size) < right.substr(0, size);
}


template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const std::string& prefix)
{
	RandomIt left_iter = std::lower_bound(range_begin, range_end, prefix, lower_comparator);

	RandomIt right_iter = std::upper_bound(range_begin, range_end, prefix, upper_comparator);

	return std::make_pair(left_iter, right_iter);
}

int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
    }
    cout << endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}

/*
moscow motovilikha
2 2
3 3
*/