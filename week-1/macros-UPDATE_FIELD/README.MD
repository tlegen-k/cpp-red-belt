## C++ Red belt
This repository contains my solutions to tasks from week 1 of [C++ course](https://www.coursera.org/learn/c-plus-plus-yellow/home/welcome)

### Macros UPDATE_FIELD

We will continue working on the AviaScanner flight search service. Our service stores a database of tickets in the form of vector <AirlineTicket>, where AirlineTicket is the same structure as in the previous task. From time to time, our service bypasses the websites of airlines, collects the latest information about available tickets and updates the records in its database. This is done using the void UpdateTicket function (AirlineTicket & ticket, const map <string, string> & updates). The updates parameter contains pairs (field name; new value). However, it contains only those fields that have changed. An example of how the UpdateTicket function works:
```cpp
void UpdateTicketExample() {
  AirlineTicket t;
  t.price = 5000;
  t.from = "DME";
  t.to = "AER";

  const map<string, string> updates = {
    {"price", "3500"},
    {"from", "VKO"}
  };
  UpdateTicket(t, updates);
  ASSERT_EQUAL(t.from, "VKO");
  ASSERT_EQUAL(t.to, "AER");
  ASSERT_EQUAL(t.price, 3500);
}
```
We need to implement function UpdateTicket so:
```cpp
void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  map<string, string>::const_iterator it;

  it = updates.find("to");
  if (it != updates.end()) {
    ticket.to = it->second;
  }

  it = updates.find("from");
  if (it != updates.end()) {
    ticket.from = it->second;
  }

  it = updates.find("price");
  if (it != updates.end()) {
    istringstream is(it->second);
    is >> ticket.price;
  }

  ...
}
```
There is code duplication here - the code blocks inside the UpdateTicket function differ only in the field name (of course, the first two blocks are not the same as the third, but they can be easily reduced to it). In this case, the field name is used not only to refer to the AirlineTicket structure, but also as a string literal. Therefore, you can write a macro that will greatly simplify the UpdateTicket function:
```cpp
#define UPDATE_FIELD(ticket, field, values) ...

void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  UPDATE_FIELD(ticket, to, updates);
  UPDATE_FIELD(ticket, from, updates);
  UPDATE_FIELD(ticket, price, updates);
  UPDATE_FIELD(ticket, airline, updates);
  ...
}
```
Write the UPDATE_FIELD macro. You are given a file airline_ticket.h containing declarations of Time, Date and AirlineTicket structures, as well as a solution template in the form of a cpp file update_field.cpp. Send the cpp file for verification, which

- includes the header file airline_ticket.h
- contains the UPDATE_FIELD macro
- contains the definitions of the operators needed to read the Date and Time classes from the istream and use them in the ASSERT_EQUAL macro (see the unit tests in the update_field.cpp file for the input format)
