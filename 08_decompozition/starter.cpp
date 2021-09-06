#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

istream& operator >> (istream& is, QueryType& q) {
	string operation_code{};
	is >> operation_code;
	if (operation_code == "NEW_BUS") { q = QueryType::NewBus; }
	else if (operation_code == "BUSES_FOR_STOP") { q = QueryType::BusesForStop; }
	else if (operation_code == "STOPS_FOR_BUS") { q = QueryType::StopsForBus; }
	else { q = QueryType::AllBuses; }
	return is;
}

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
  is >> q.type;
  string s;
  switch(q.type)
  {
	case QueryType::NewBus:
	is >> q.bus;
	int stop_count;
	is >> stop_count;
	while(is) { is >> s; q.stops.push_back(s); }
	break;

	case QueryType::BusesForStop:
	is >> q.stop;
	break;

	case QueryType::StopsForBus:
	is >> q.bus;
	break;

	case QueryType::AllBuses: break;
  }
  
  return is;
}

struct BusesForStopResponse {
  // Наполните полями эту структуру

};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
  return os;
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
  return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
  map<string, vector<string> > buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
		cout << "No buses" << endl;
	} else {
		for (const auto& bus_item : r.buses_to_stops) {
			cout << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				cout << stop << " ";
			}
			cout << endl;
		}
	}
	return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
	for (const string& stop : stops) {
	all_buses.buses_to_stops[bus].push_back(stop);
	}
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
    return {};
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
    return {};
  }

  AllBusesResponse GetAllBuses() const {
    return all_buses;
  }

private:
	AllBusesResponse all_buses;
	BusesForStopResponse stops_to_buses;
	StopsForBusResponse buses_to_stop;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
