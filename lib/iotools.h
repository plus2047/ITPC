#pragma once

// this is a debug library.
// so donot care about performance.
#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

namespace contest {
template <int group = 16, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
#endif
}

#define echo(args...) (fprintf(stderr, args), printf(args))

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
}  // namespace contest