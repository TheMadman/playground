#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

using set = std::unordered_set<int>;
using dict = std::unordered_map<int, int>;
template <typename T>
using vector = std::vector<T>;

/*
 * This function is only necessary if you're using
 * C++ older than C++20
 *
 * Ubuntu LTS/Debian have old compilers
 */
template <typename Key, typename Value>
bool contains(const std::unordered_map<Key, Value> &map, const Key &key)
{
    return map.find(key) != end(map);
}

set intersection(const vector<set> &sets)
{
    dict counts;
    for (auto &set : sets) {
        for (auto &value : set) {
            if (contains(counts, value)) {
                counts[value]++;
            } else {
                counts[value] = 1;
            }
        }
    }

    int number_sets = sets.size();
    set result;
    for (auto &record : counts) {
        auto value = record.first;
        auto count = record.second;
        if (count == number_sets) {
            result.insert(value);
        }
    }

    return result;
}

int main()
{
    set first{ 1, 3, 5, 7, 9, };
    set second{ 1, 2, 3, 5, 8, };

    vector<set> sets{ first, second };

    auto result = intersection(sets);
    for (const auto &value : result) {
        std::cout << value << std::endl;
    }
}
