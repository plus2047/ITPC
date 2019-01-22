#pragma once
#include <algorithm>
#include <cstdio>

// ===== string match problem =====
// 1. if pattern length is constant, use hash map.
// 2. if just search one time, use kmp. (so kmp is not so useful.)
// 3. suffix tree for match any substring with any length.

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

// ===== string tree =====
template <int symbol_num>
struct StringTreeNode {
    int child[symbol_num];
    int index;  // if multi match is needed, change this into a vector.
    StringTreeNode() : index(-1) { std::fill(child, child + symbol_num, -1); }
};
template <typename CHAR = char, int symbol_num = 26>
struct StringTree {
    // usage:
    // insert some string into this string tree:
    //   string_tree.run(str_begin, str_end, str_index, true);
    // and than find if string exist in the string tree:
    //   int str_index;
    //   string_tree.run(str_begin, str_end, str_index, false);
    // because insert & find algorithm is very similiar, merge them
    // into one function.
    // function run will return false if it's neither a match or a prefix.
    // return true if it's a string inserted or a prefix of one of inserted
    // string.
    //   for the first case, it will save string id into the last param.
    //   for the second case, it will save -1 into the last param.
    // this struct can be used as suffix trie to quick search any pattern.
    typedef StringTreeNode<symbol_num> Node;
    std::vector<Node> nodes;

    // a function pointer to convert a char into it's index.
    // e.g. [](char c){return c - 'a';}
    int (*get_index)(CHAR);
    StringTree(int (*_get_index)(const CHAR)) {
        nodes.push_back(Node());
        get_index = _get_index;
        // root is always nodes[0].
        // after init, this is a empty tree.
        // even "" is not in this tree.
    }
    StringTree() {
        nodes.push_back(Node());
        get_index = [](CHAR c) { return c - 'a'; };
    }

    bool run(CHAR* begin, CHAR* end, int& index, bool is_insert) {
        // root index is alway 0.
        // this function suggest nodes[root_index] exists.
        int root_index = 0;
        for (; begin != end; ++begin) {
            // dangerous: reference to variable saved in std container.
            // this reference should be safe before any change to the container.
            int& child = nodes[root_index].child[get_index(*begin)];
            if (child == -1) {
                if (is_insert) {
                    // donot change this order.
                    // if push_back at first, the reference can be invalid.
                    child = nodes.size();
                    nodes.push_back(Node());
                } else {
                    return false;
                }
            }
            root_index = child;
        }
        if (is_insert) {
            nodes[root_index].index = index;
        } else {
            index = nodes[root_index].index;
        }
        return true;
    }

    void print() {
        for (int i = 0; i < nodes.size(); i++) {
            std::printf("node id: %d, index: %d, child:", i, nodes[i].index);
            for (int j = 0; j < symbol_num; j++) {
                std::printf("%d ", nodes[i].child[j]);
            }
            std::printf("\n");
        }
    }
};
}  // namespace contest
