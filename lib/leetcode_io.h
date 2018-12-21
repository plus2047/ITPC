#ifndef __LEETCODE_H__
#define __LEETCODE_H__

#include <iostream>
#include <string>
#include <vector>

template <typename NUM>
std::vector<NUM> get_vector() {
    std::string line;
    std::cin >> line;
    assert(line.size() >= 2 and line.front() == '[' and line.back() == ']');
    std::stringstream s(line);
    char _c;
    NUM _n;
    std::vector<NUM> res;
    while (s >> _c && s >> _n) {
        res.push_back(_n);
    }
    return res;
}

template <typename NUM>
NUM get_num() {
    NUM _n;
    std::cin >> _n;
    return _n;
}

#endif  // define __LEETCODE_H__