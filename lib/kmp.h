#pragma once

#include <algorithm>
#include <cstdio>
#include <string>

namespace contest {

// ===== kmp algoithm =====
// next[i] is the longest number n, s.t.
// p[0:n] == p[i+1-n:i+1] (define next_p[0] = 0)
// this implement is better than ITPC and GeeksForGeeks.
// =====
// the most important part of kmp is to understand what next array means
// and MEMORIZE THOSE CODE!
// if you forget those code, try to understand function `kmp_find` at first.
// kmp next array is very useful for questions about prefix-suffix.

template <typename STR>
void kmp_init(const STR& pattern, std::vector<int>& next) {
    next[0] = 0;
    for (int i = 1, j = 0; i < int(pattern.size()); ++i) {
        while (j and pattern[j] != pattern[i]) j = next[j - 1];
        if (pattern[i] == pattern[j]) ++j;
        next[i] = j;
    }
}

template <typename STR>
int kmp_find(const STR& pattern, const STR& target,
             const std::vector<int>& next) {
    for (int i = 0, j = 0; i < int(target.size()); i++) {
        while (j and pattern[j] != target[i]) j = next[j - 1];
        if (pattern[j] == target[i]) ++j;
        if (j == int(pattern.size())) return i - j + 1;
    }
    return -1;
}
}  // namespace contest
