#include <iostream>
#include <queue>
#include <map>
#include <fstream>
#include <string>
#include "profile.h"
#include "test_runner.h"
using namespace std;

class Event
{
public:
    //- Construct from given input values
    Event(const int64_t& time, const string& hotel_name,
          const u_int& client_id, const int& room_count) :
    time_(time),
    hotel_name_(hotel_name),
    client_id_(client_id),
    room_count_(room_count)
    {}

    int64_t Time()
    {
        return time_;
    }
    string HotelName()
    {
        return hotel_name_;
    }
    u_int ClientID()
    {
        return client_id_;
    }
    int RoomCount()
    {
        return room_count_;
    }

private:
    int64_t time_;
    string  hotel_name_;
    u_int   client_id_;
    int     room_count_;
};

class BookingManager {
public:
    BookingManager():
    events_(),
    hotel_clients_(),
    hotel_rooms_()
    {}
    //- Book current room_count in hotel_name by client_id at time
    void Book(const int64_t& time, const string& hotel_name,
              const u_int& client_id, const int& room_count)
    {
        //- Add event to queue of events
        events_.push({time, hotel_name, client_id, room_count});

        //- If not in map add pair, otherwise increase room count
            hotel_rooms_[hotel_name] += room_count;

        //- Map [] operator creates key if not in map and initializes
        // value to 0, otherwise we add room_count to old value
            hotel_clients_[hotel_name][client_id] += room_count;
    }

    //- Return total number of clients reservations in hotel_name in last 24hr
    u_int Clients(const string& hotel_name)
    {
        if (hotel_clients_.find(hotel_name) == hotel_clients_.end() ||
            hotel_clients_.empty())
        {
            return 0;
        }
        else
        {
            Adjust(events_.back().Time());
            return hotel_clients_[hotel_name].size();
        }
    }
    //- Return number of rooms reserved in hotel_name in last 24 hr
    int Rooms(const string& hotel_name )
    {
        if (hotel_rooms_.find(hotel_name) == hotel_rooms_.end() ||
            hotel_rooms_.empty())
        {
            return 0;
        }
        else
        {
            Adjust(events_.back().Time());
            return hotel_rooms_[hotel_name];
        }
    }

private:
    static const int MAX_HOTEL_COUNT_ = 100'000;
    queue<Event> events_;
    map<string, map<u_int,int>> hotel_clients_;
    map<string, int> hotel_rooms_;

    void Adjust(int64_t time)
    {
    //- Delete events older than 24 hr from queue<Event>
        while (!events_.empty() && events_.front().Time() <= time - 86400)
        {
            int room_count = events_.front().RoomCount();
            u_int client_id = events_.front().ClientID();
            string hotel_name = events_.front().HotelName();

            events_.pop();

            //- Reduce clients' rooms reservations by the amount of old events
            hotel_clients_[hotel_name][client_id] -= room_count;

            //- Erase if wrong number of rooms
            if (hotel_clients_[hotel_name][client_id] <= 0)
            {
                hotel_clients_[hotel_name].erase(client_id);
            }
            //- If map empty erase key value pair
            if ( hotel_clients_[hotel_name].empty())
            {
                hotel_clients_.erase(hotel_name);
            }
            //- Same logic
            hotel_rooms_[hotel_name] -=  room_count;
            if (hotel_rooms_[hotel_name] <= 0)
            {
                hotel_rooms_.erase(hotel_name);
            }

        }

    }
};

void Test() {
    BookingManager manager;
    std::string marriot{ "mariott" };
    std::string hilton{ "hilton" };
    // Test empty bookings
    ASSERT_EQUAL(manager.Clients(marriot), 0);
    ASSERT_EQUAL(manager.Rooms(marriot), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.Clients(marriot), 4);
    ASSERT_EQUAL(manager.Rooms(marriot), 13);
    ASSERT_EQUAL(manager.Clients(hilton), 2);
    ASSERT_EQUAL(manager.Rooms(hilton), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients(marriot), 1);
    ASSERT_EQUAL(manager.Rooms(marriot), 1);
    ASSERT_EQUAL(manager.Clients(hilton), 1);
    ASSERT_EQUAL(manager.Rooms(hilton), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients(marriot), 2);
    ASSERT_EQUAL(manager.Rooms(marriot), 2);
    ASSERT_EQUAL(manager.Clients(hilton), 0);
    ASSERT_EQUAL(manager.Rooms(hilton), 0);

}
void Test2()
{
BookingManager b;

ASSERT_EQUAL(b.Rooms("a"),0);
ASSERT_EQUAL(b.Clients("a"),0);

ASSERT_EQUAL(b.Rooms("b"),0);
ASSERT_EQUAL(b.Clients("c"),0);

b.Book(-100000,"a",100000,1000);
b.Book(-100000,"a",100003,1000);
b.Book(-100000,"b",100002,1000);
ASSERT_EQUAL(b.Rooms("a"),2000);
ASSERT_EQUAL(b.Clients("a"),2);

b.Book(-10000,"a",100002,1000);
ASSERT_EQUAL(b.Rooms("a"),1000);
ASSERT_EQUAL(b.Clients("a"),1);
ASSERT_EQUAL(b.Rooms("b"),0);
ASSERT_EQUAL(b.Clients("b"),0);
}
void Test3()
{
BookingManager a;
a.Book(1, "RED", 11, 4);
a.Book(50000, "RED", 11 ,5);
a.Book(90000, "RED", 22, 2);
ASSERT_EQUAL(a.Clients("RED"), 2);
ASSERT_EQUAL(a.Rooms("RED"), 7);
}

void TestClients() {
    BookingManager bm;
    bm.Book(0, "q", 0, 1);
    ASSERT_EQUAL(bm.Clients("q"), 1);
    ASSERT_EQUAL(bm.Rooms("q"), 1);
    bm.Book(10, "q", 0, 3 );
    ASSERT_EQUAL(bm.Clients("q"), 1);
    ASSERT_EQUAL(bm.Rooms("q"), 4);
    bm.Book( 86411, "q", 3, 1);
    ASSERT_EQUAL(bm.Clients("q"), 1);
    ASSERT_EQUAL(bm.Rooms("q"), 1);
}

int main() {
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BookingManager manager;

    // page count <= 10e3
    int query_count; // Q~10^6

    cin >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            u_int client_id;
            cin >> client_id;
            int room_count;
            cin >> room_count;
            manager.Book(time,hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << endl;
        }
        else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << endl;
        }
    }
    return 0;
}
