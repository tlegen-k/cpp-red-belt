#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <set>
using namespace std;
//Q=10^5
class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish); //O(1)
        reachable_lists_[finish].insert(start); //O(1)
    }
    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish); //O(1)
        if (reachable_lists_.count(start) < 1) { // log(Q)
            return result;
        }

        const set<int>& reachable_stations = reachable_lists_.at(start);

            const auto finish_pos = reachable_stations.lower_bound(finish);
            if (finish_pos != end(reachable_stations)) {
                result = min(result, abs(finish - *finish_pos));
            }
            if (finish_pos != begin(reachable_stations)) {
                result = min(result, abs(finish - *prev(finish_pos)));
            }
        return result; // total complexity = O(log(Q) + 10e9) ~ O(10e9)
    }
private:
    map<int, set<int>> reachable_lists_;
};


int main() {
    RouteManager routes;

    int query_count;
    cin >> query_count; // Q ~ 10e5

    for (int query_id = 0; query_id < query_count; ++query_id) { //Q
        string query_type;
        cin >> query_type;
        int start, finish; // 10e9
        cin >> start >> finish; //N ~ 10^9
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
