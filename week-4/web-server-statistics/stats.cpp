
#pragma once

#include "stats.h"
#include <vector>
using namespace std;

Stats::Stats() : method_stats ({{"GET",     0},
                         {"PUT",     0},
                         {"POST",    0},
                         {"DELETE",  0},
                         {"UNKNOWN", 0}}),
          uri_stats ({{"/",        0},
                      {"/order",   0},
                      {"/product", 0},
                      {"/basket",  0},
                      {"/help",    0},
                      {"unknown",  0}}) {}

void Stats::AddMethod(string_view method) {

    if (method_stats.find(method) != method_stats.end())
    {
        ++method_stats[method];
    } else {
        ++method_stats["UNKNOWN"];
    }
}

void Stats::AddUri(string_view uri) {
    if (uri_stats.find((uri)) != uri_stats.end()) {
        ++uri_stats[uri];
    } else {
        ++uri_stats["unknown"];
    }
}

const map<string_view, int> & Stats::GetMethodStats() const {
    return method_stats;
}

const map<string_view, int> & Stats::GetUriStats() const {
    return uri_stats;
}

HttpRequest ParseRequest(string_view line)
{
    HttpRequest request;
    string item;

    istringstream iss(string(line), std::ios_base::in);

    size_t first = 0;
    std::vector<std::string_view> output;

    while (first < line.size())
    {
        const auto second = line.find_first_of(' ', first);

        if (first != second) {
            output.emplace_back(line.substr(first, second-first));
        }
        if (second == std::string_view::npos)
            break;

        first = second + 1;
    }
    request.method = output[0];
    request.uri = output[1];
    request.protocol = output[2];
    return request;
}
