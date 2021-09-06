#pragma once

#include "date.h"

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>


class Database {
public:
  void Add(const Date& date, const string& event);
  void Print(ostream& stream) const;

  template<typename Func>
  int RemoveIf(Func func) {
    int counter{0};
    for (auto it = storage.begin(); it != storage.end(); ) {
      auto border = stable_partition(it->second.begin(), it->second.end(), [it, func] (string& event) { return func(it->first, event); });
      it->second.erase(it->second.begin(), border);
      counter += border - it->second.begin();
      if (it->second.empty()) { it = storage.erase(it); }
      else { ++it; }
    }
    return counter; 
  }

  template<typename Func>
  vector<pair<Date, string> > FindIf(Func func) const {
    vector<pair<Date, string> > result;
    for (const auto& pair : storage) {
      for (const auto& event : pair.second) {
        bool pr = func(pair.first, event);
        if (pr) { result.push_back(make_pair(pair.first, event)); }
      }
    }
    return result;
  }

  pair<Date, string> Last(const Date& date) const;

private:
  map<Date, vector<string>> storage;
};

ostream& operator<<(ostream& os, const pair<Date, string>& pair);
