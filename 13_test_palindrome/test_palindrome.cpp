#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
}

void Test_IsPalindrom() {
  AssertEqual(IsPalindrom(""), true, "1");
  {
    string s{"h"};
    AssertEqual(IsPalindrom(s), true, "2");
  }
  AssertEqual(IsPalindrom("wow wow"), true, "3");
  AssertEqual(IsPalindrom(" "), true, "4");

  AssertEqual(IsPalindrom("ow w"), false, "5");
  AssertEqual(IsPalindrom("w ow"), false, "6");
  AssertEqual(IsPalindrom("  lool   "), false, "7");
  AssertEqual(IsPalindrom("     l   "), false, "8");
  AssertEqual(IsPalindrom("ab"), false, "9");

  AssertEqual(IsPalindrom("ll    ll    ll"), true, "10");
  AssertEqual(IsPalindrom("baobab"), false, "11");
  AssertEqual(IsPalindrom(""), true, "1");
  AssertEqual(IsPalindrom("abcderdcba"), 0, "12");
  AssertEqual(IsPalindrom("abcdeedcbaz"), 0, "13");
  AssertEqual(IsPalindrom("zabcdeedcba"), 0, "14");
}

int main() {
  TestRunner runner;
  runner.RunTest(Test_IsPalindrom, "Test_IsPalindrom");
  return 0;
}
