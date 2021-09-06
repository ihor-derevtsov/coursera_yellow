#include "database.h"

using namespace std;

void Database::Add(const Date& date, const string& event) {
  const auto& link = storage[date];
  if (count(link.begin(), link.end(), event) == 0) {
    storage[date].push_back(event);
  }
}

void Database::Print(ostream& stream) const {
  for (const auto& item : storage) {
    for (const string& event : item.second) {
      stream << item.first << " " << event << endl;
    }
  }
}

pair<Date, string> Database::Last(const Date& date) const {
  if (storage.empty()) { throw invalid_argument("Empty storage"); }
	auto upper = storage.upper_bound(date);
  if (upper == storage.begin()) { throw invalid_argument("Less date"); }
	--upper;
	return make_pair(upper->first, upper->second.back());
}

ostream& operator<<(ostream& os, const pair<Date, string>& pair) {
  os << pair.first << " " << pair.second;
  return os;
}