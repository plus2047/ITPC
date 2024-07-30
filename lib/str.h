#pragma once

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

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

template <typename STR>
void kmp_find_all(const STR& pattern, const STR& target,
                  const std::vector<int>& next,
                  std::vector<int>& matches) {
    for (int i = 0, j = 0; i < int(target.size()); i++) {
        while (j and pattern[j] != target[i]) j = next[j - 1];
        if (pattern[j] == target[i]) ++j;
        if (j == int(pattern.size())) matches.push_back(i);
    }
}

// Longest palindromic substring, Manacher algorithm
// https://zh.wikipedia.org/wiki/%E6%9C%80%E9%95%BF%E5%9B%9E%E6%96%87%E5%AD%90%E4%B8%B2
std::vector<int> manachar(const std::string& s) {
    const char nil = '#', head = '^', tail = '$';
    std::string t(s.size() * 2 + 1, nil);
    int m = s.size(), n = t.size();
    t[0] = head, t[n - 1] = tail;
    for(int i = 0; i < m; i++) {
        t[i * 2 + 2] = s[i];
    }
    std::vector<int> arm(n, 0);
    int right = 0, center = 0;
    for(int i = 1; i < n - 1; i++) {
        if(i < right) {
            arm[i] = std::min(right - i, arm[center * 2 - i]);
        }
        while(t[i + arm[i] + 1] == t[i - arm[i] - 1]) {
            arm[i]++;
        }
        if(i + arm[i] > right) {
            right = i + arm[i], center = i;
        }
    }
    std::vector<int> res(m, 0);
    for(int i = 0; i < m; i++) {
        res[i] = arm[i * 2 + 2] / 2;
    }
    return res;
}

}  // namespace contest
