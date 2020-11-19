## Macros generator

Let's pretend that you are developing the innovative AviaScanner flight search service. Your service presents an air ticket as a structure
```cpp
struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  uint64_t price;
};
```
You are currently working on sorting search results. The user enters his request and receives a list of eligible tickets. Then he can set the sorting parameters of this list. For example, first by price, then by departure time and, finally, by arrival airport.

To implement sorting like in the example, you can use the [digital sorting algorithm](https://en.wikipedia.org/wiki/Radix_sort):
```cpp
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.to < rhs.to;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.departure_time < rhs.departure_time;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.price < rhs.price;
  });
 ```
As you can see, there is code duplication in the example above - we had to write three lambda functions that differ only in the field by which the sorting is performed. You can get rid of this duplication by writing the SORT_BY macro and applying it as follows:
```cpp
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), SORT_BY(to));
  stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
  stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}
```
Write a macro SORT_BY that takes a field name in the AirlineTicket structure as a parameter. The call to sort (begin (tixs), end (tixs), SORT_BY (some_field)) should sort the tixs vector by some_field.

You are given a file airline_ticket.h containing declarations of the Time, Date and AirlineTicket structures, as well as a solution template in the form of a sort_by.cpp cpp file. Send the cpp file for verification, which

- includes the header file airline_ticket.h
- contains the SORT_BY macro
- contains definitions of operators required to use the Date and Time classes in the sorting algorithm and the ASSERT_EQUAL macro (you can choose any format for output to the stream)
