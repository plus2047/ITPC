#!/usr/bin/env python
# -*- coding: utf-8 -*-


def get_lps(s):
    s_len = len(s)
    lps = [0] * s_len

    pre, i = 0, 1
    while i < s_len:
        if s[i] == s[pre]:
            lps[i] = pre + 1
            i += 1; pre += 1
        else:
            if pre == 0:
                lps[i] = 0
                i += 1
            else:
                pre = lps[pre - 1]

    return lps


def search(s, pattern):
    s_len, p_len = len(s), len(pattern)
    lps = get_lps(pattern)

    i = j = 0
    while i < s_len:
        if s[i] == pattern[j]:
            i += 1; j += 1
            if j == p_len:
                return i - j
        else:
            if j == 0:
                i += 1
            else:
                j = lps[j - 1]

    return -1


if __name__ == "__main__":
    s = "ABCABAABCABAC"
    p = "CAB"
    print("find %s in %s at: %s." % (s, p, search(s, p)))

