#pragma once

#include <algorithm>
#include <cstdio>

namespace contest {
// ===== kmp algoithm =====
// next_p[i] is the longest number n, s.t.
// p[0:n] == p[i+1-n:i+1] (define next_p[0] = 0)
// this implement is better than ITPC and GeeksForGeeks.
// =====
// the most important part of kmp is to understand what next array means
// and MEMORIZE THOSE CODE!
// if you forget those code, try to understand function `kmp_match` at first.
// kmp next array is very useful for questions about prefix-suffix.
template <typename STR_P, typename NEXT_P>
int kmp_match(STR_P pattern_p, STR_P target_p, NEXT_P next_p, int pattern_len,
              int str_len) {
    for (int i = 0, j = 0; i < str_len; i++) {
        while (j and pattern_p[j] != target_p[i]) j = next_p[j - 1];
        if (pattern_p[j] == target_p[i]) ++j;
        if (j == pattern_len) return i - j + 1;
    }
    return -1;
}
template <typename STR_P, typename NEXT_P>
void get_kmp_next(STR_P pattern_p, NEXT_P next_p, int pattern_len) {
    next_p[0] = 0;
    for (int i = 1, j = 0; i < pattern_len; ++i) {
        while (j and pattern_p[j] != pattern_p[i]) j = next_p[j - 1];
        next_p[i] = (j += pattern_p[j] == pattern_p[j]);
    }
}
}  // namespace contest
