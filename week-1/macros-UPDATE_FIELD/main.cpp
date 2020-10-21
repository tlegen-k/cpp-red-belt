#include "airline_ticket.h"
#include "test_runner.h"
#include <iomanip>
#include <string>
#include <istream>
#include <sstream>
using namespace std;
bool operator==(const Date &lhs, const Date &rhs) {
    return ((lhs.day == rhs.day) &&
            (lhs.month == rhs.month) &&
            (lhs.year == rhs.year));
}
bool operator<(const Date &lhs, const Date &rhs) {
    if (lhs.year< rhs.year) {
        return true;
    }
    if (lhs.year > rhs.year) {
        return false;
    }
    if (lhs.month > rhs.month) {
        return false;
    }
    if (lhs.month < rhs.month) {
        return true;
    }
    return (lhs.day < rhs.day);
}
ostream& operator<<(ostream& os, const Date& date) {
    os << setfill('0') << setw(4) << date.year << '-';
    os << setfill('0') << setw(2) << date.month << '-';
    os << setfill('0') << setw(2) << date.day;
    return os;
}
istream& operator>>(istream& is, Date& date) {
    is >> date.year;
    is.ignore(1);
    is >> date.month;
    is.ignore(1);
    is >> date.day;
    return is;
}
bool operator==(const Time &lhs, const Time &rhs) {
    return ((lhs.hours == rhs.hours) &&
            (lhs.minutes == rhs.minutes));
}
bool operator<(const Time &lhs, const Time &rhs) {
    if (lhs.hours < rhs.hours) {
        return true;
    }
    if (lhs.hours > rhs.hours) {
        return false;
    }
    return (lhs.minutes < rhs.minutes);
}
ostream& operator<<(ostream& os, const Time& time) {
    os << setfill('0') << setw(2) << time.hours << ':';
    os << setfill('0') << setw(2) << time.minutes;
    return os;
}
istream& operator>>(istream& is, Time& time){
    is >> time.hours;
    is.ignore(1);
    is >> time.minutes;
    return is;
}

std::map<string,string>::iterator it;
#define UPDATE_FIELD(ticket, field, values) \
({                                         \
    auto it = values.find(#field);         \
    if (it != values.end()) {              \
        istringstream is(it->second);       \
        is >> ticket.field;}                \
    else {}                                 \
})
void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
            {"price", "12550"},
            {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
