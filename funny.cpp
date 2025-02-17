#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string.h>
#include <vector>
using namespace std;

typedef long long ll;

set<set<size_t>>
generateCombinationsInternal(vector<pair<ll, bool>> &entries, ll crrVal) {

    if (crrVal == 0)
        return {{}};

    set<set<size_t>> res;

    for (size_t i = 0; i < entries.size(); i++) {
        auto &next = entries[i];
        ll value = next.first;
        ll available = next.second;
        if (available <= 0)
            continue;

        ll nextVal = crrVal - value;
        if (nextVal < 0)
            break;

        next.second = false;
        auto nextRes = generateCombinationsInternal(entries, nextVal);
        next.second = true;

        for (auto x : nextRes) {
            x.insert(i);
            res.insert(std::move(x));
        }
    }

    return res;
}

set<set<size_t>> generateCombinations(vector<pair<ll, string>> &entries, ll target) {
    vector<pair<ll, bool>> newEntries;
    newEntries.reserve(entries.size());

    for (auto &entry : entries) {
        newEntries.push_back(make_pair(entry.first, true));
    }

    return generateCombinationsInternal(newEntries, target);
}

int main(void) {

    ll target;
    auto _ = scanf("%lld\n", &target);

    if (target < 0) {
        fprintf(stderr, "Target cannot be less than 0\n");
        return 1;
    }

    printf("Target: %lld\n\n", target);

    vector<pair<ll, string>> entries;

    while (true) {
        string s;
        getline(cin, s);

        printf("%s\n", s.c_str());

        if (s.length() == 0)
            break;

        auto it = find_if(s.begin(), s.end(),
                          [](char c) { return c >= '0' && c <= '9'; });

        if (it == s.end()) {
            fprintf(stderr, "Malformed input: entry %zu has no value\n",
                    entries.size() + 1);
            return 1;
        }

        ll value = atoi(s.c_str() + (it - s.begin()));
        entries.push_back(make_pair(value, s));
    }

    sort(entries.begin(), entries.end());

    auto res = generateCombinations(entries, target);

    if (res.empty()) {
        printf("No solutions found\n");
        return 0;
    }

    ll solIdx = 0;
    for (auto &sol : res) {
        solIdx++;
        printf("Solution %lld: \n", solIdx);
        for (ll entryIdx : sol) {
            printf("    %s\n", entries[entryIdx].second.c_str());
        }
        printf("\n");
    }

    return 0;
}
