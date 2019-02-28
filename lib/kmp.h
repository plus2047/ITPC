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
// if you forget those code, try to understand function `match` at first.
// kmp next array is very useful for questions about prefix-suffix.
template <typename STR = std::string>
struct KMP {
    STR pattern;
    std::vector<int> next;
    int pattern_len;

    explicit KMP(const STR& pattern_)
        : pattern(pattern_), next(pattern_.size()) {
        init();
    }

    void init() {
        // generate 'next' array for pattern.
        pattern_len = int(pattern.size());
        next.resize(pattern_len);
        // get 'next' array:
        next[0] = 0;
        for (int i = 1, j = 0; i < pattern_len; ++i) {
            while (j and pattern[j] != pattern[i]) j = next[j - 1];
            if (pattern[i] == pattern[j]) ++j;
            next[i] = j;
        }
    }

    int match(const STR& target) {
        int str_len = int(target.size());
        for (int i = 0, j = 0; i < str_len; i++) {
            while (j and pattern[j] != target[i]) j = next[j - 1];
            if (pattern[j] == target[i]) ++j;
            if (j == pattern_len) return i - j + 1;
        }
        return -1;
    }
};
}  // namespace contest
