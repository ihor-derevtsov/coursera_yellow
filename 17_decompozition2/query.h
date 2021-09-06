/*
enum class QueryType
struct Query
объявление istream& operator >> (istream& is, Query& q) 
*/

#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q);