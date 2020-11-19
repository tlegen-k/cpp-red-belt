#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include "profile.h"

#include "test_runner.h"
using namespace std;

class ReadingManager {
public:
ReadingManager() :
        user_info_(),
        pages_info_(1001, 0) {}

void Read(int user_id, int page_count) {
    // If user_id already in map update page_count
    int previous_page = 0;
    if (user_info_.count(user_id) != 0)
    {
        previous_page = user_info_.at(user_id);

        user_info_.at(user_id) = page_count;
    }
    // Otherwise, add pair and update pages_info_
    else
    {
        user_info_.insert(make_pair(user_id, page_count));
        previous_page = 0;
    }

    for (int i = previous_page + 1; i <= page_count; i++)
    {
        pages_info_[i]++;
    }
}

double Cheer(int user_id) const {
    if (user_info_.count(user_id) == 0)
    {
        return 0;
    }
    else
    {
        int page = user_info_.at(user_id);
        double res = (pages_info_[1] - pages_info_[page]) * 1.0 /
                (pages_info_[1] - 1) * 1.0;
        if ( (pages_info_[1] - pages_info_[page]) == 0 &&
                (pages_info_[1] - 1) == 0  )
        {
            return 1;
        }
        else
        {
            return res;
        }
    }

}

private:
map<int, int> user_info_; // users id and page count
vector<int> pages_info_; // stores number of users that read till that point
// page count <= 10e3
};

void TestRead() {
    ReadingManager manager;

    ASSERT_EQUAL(0, manager.Cheer(5));
    manager.Read(1, 10);
    ASSERT_EQUAL(1, manager.Cheer(1));
    manager.Read(2, 5);
    manager.Read(3, 7);
    ASSERT_EQUAL(0, manager.Cheer(2));
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    manager.Read(3, 10);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    manager.Read(3, 11);
    ASSERT_EQUAL(1, manager.Cheer(3));
    ASSERT_EQUAL(0.5, manager.Cheer(1));
    manager.Read(2, 11);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    ASSERT_EQUAL(0.5, manager.Cheer(2));
    manager.Read(2, 12);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    ASSERT_EQUAL(1, manager.Cheer(2));
    manager.Read(1, 13);
    manager.Read(2, 13);
    manager.Read(3, 13);
    ASSERT_EQUAL(0, manager.Cheer(1));
    ASSERT_EQUAL(0, manager.Cheer(2));
    ASSERT_EQUAL(0, manager.Cheer(3));
}

int main() {
// Для ускорения чтения данных отключается синхронизация
// cin и cout с stdio,
// а также выполняется отвязка cin от cout
ios::sync_with_stdio(false);
    cin.tie(nullptr);

ReadingManager manager;

// page count <= 10e3
int query_count; // Q~10^6

cin >> query_count;




for (int query_id = 0; query_id < query_count; ++query_id)
{
    string query_type;
        cin >> query_type;

    int user_id; // N~10^5
        cin >> user_id;

    if (query_type == "READ") {
        int page_count; // P~10^3
          cin >> page_count;
        manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
        cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
}

    TestRunner tr;
    RUN_TEST(tr, TestRead);
return 0;
}
