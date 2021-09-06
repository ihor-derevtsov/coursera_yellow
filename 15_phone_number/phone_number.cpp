#include "phone_number.h"
// #include "../09_UNIT_TESTING_FRAMEWORK/test_runner.h"

#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream ss(international_number);
    if (ss.peek() != '+') { throw invalid_argument("Invalid argument"); }
    ss.ignore(1);
    getline(ss, country_code_, '-');
    // cout << "country: " << country_code_ << endl;
    getline(ss, city_code_, '-');
    // cout << "city: " << city_code_ << endl;
    getline(ss, local_number_);
    // cout << "local: " << local_number_ << endl;
    if (!ss) { throw invalid_argument("Invalid argument"); }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}


string PhoneNumber::GetInternationalNumber() const {
    return ('+' + country_code_ + '-' + city_code_ + '-' + local_number_);
}
