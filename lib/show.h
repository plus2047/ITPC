#ifndef __SHOW_H__
#define __SHOW_H__

// this is a debug library.
// so donot care about performance.

#include <iostream>

namespace contest {
template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
    printf("%s", note);
    while (begin != end) {
        std::cout << *(begin++) << ' ';
    }
    std::cout << std::endl;
}

template <typename ITER>
void show(const char* note, ITER begin, ITER end, int group) {
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
}
}  // namespace contest
#endif  // define __SHOW_H__