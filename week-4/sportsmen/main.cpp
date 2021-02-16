#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    const int MAX_ATHLETES = 100'000;

    list<int> team;
    int n;
    cin >> n;
    vector<list<int>::iterator> team_pos(MAX_ATHLETES + 1, team.end());

    for (int i = 0; i < n; i++)
    {
        int number;
        int next;
        cin >> number >> next;
        team_pos[number] = team.insert(team_pos[next],number);
    }
    for (auto i : team)
    {
        cout << i << "\n";
    }
    return 0;
}
