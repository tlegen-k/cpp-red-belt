#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "profile.h"
using namespace std;


class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        int old_size = dict.size();
        dict.insert(begin(words), end(words));
        int new_size = dict.size();
        return new_size - old_size;
    }

    vector<string> KnownWords() {
        vector<string> v = {begin(dict), end(dict)};
        return v;
    }
};

int main() {
    Learner learner;
    string line;

    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}
