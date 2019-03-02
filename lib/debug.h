#pragma once

// this is a debug library.
// so donot care about performance.
#include <cstdarg>
#include <ctime>
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

std::clock_t _t0;
#define timer_begin() _t0 = clock();
#define timer_end(STR) \
    printf("%s time cost: %lf\n", STR, (clock() - _t0) / double(CLOCKS_PER_SEC))

}  // namespace contest