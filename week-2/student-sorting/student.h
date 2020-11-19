#ifndef STUDENT_SORTING_STUDENT_H
#define STUDENT_SORTING_STUDENT_H

#include <map>
#include <string>
#include "profile.h"
using namespace std;

struct Student {
    string first_name;
    string last_name;
    map<string, double> marks;
    double rating;

    bool operator < (const Student& other) const {
        return GetName() < other.GetName();
    }

    bool Less(const Student& other) const {
        LOG_DURATION("Less");
        return rating > other.rating;
    }

    string GetName() const {
        return first_name + " " + last_name;
    }
};
#endif //STUDENT_SORTING_STUDENT_H
