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

// ===== Trie =====
// Trie use pointer index to store the info about string.
// the leaf point has no child pointer, so it use extra field
// to store info about whole string.
// be careful to use Trie. map<string> is usually enough.

const int TRIE_VOID_IDX = -1;  // void val for node index.
const int TRIE_VOID_VAL = -1;  // void val for node val field.
template <typename ITER, int sym_n>
struct Trie {
    // how to get child index from a iter.
    inline int get_idx(ITER c) { return *c - 'a'; }
    // how to update val for 'insert' func.
    inline void update_val(int& old, int val) { old = val; }

    struct Node {
        int child[sym_n], val;
        Node() : val(TRIE_VOID_VAL) {
            std::fill(child, child + sym_n, TRIE_VOID_IDX);
        }
    };

    std::vector<Node> nodes = {Node()};

    bool insert(ITER begin, ITER end, int val) {
        int root_index = 0;
        for (; begin != end; ++begin) {
            // dangerous: reference to variable saved in std container.
            int& child = nodes[root_index].child[get_idx(begin)];
            if (child == TRIE_VOID_IDX) {
                root_index = child = nodes.size();
                nodes.push_back(Node());
            } else {
                root_index = child;
            }
        }
        bool unseen = nodes[root_index].val == TRIE_VOID_VAL;
        update_val(nodes[root_index].val, val);
        return unseen;
    }

    // return true if it is a prefix.
    // and if it's a full match, save the string index into idx.
    bool check(ITER begin, ITER end, int& val) {
        int root_index = 0;
        for (; begin != end; ++begin) {
            int child = nodes[root_index].child[get_idx(begin)];
            if (child == TRIE_VOID_IDX) return false;
            root_index = child;
        }
        val = nodes[root_index].val;
        return true;
    }

    // use '.' to fuzzy match any char.
    // return true if full match any.
    bool dot_fuzzy(int root_index, ITER begin, ITER end) {
        while (begin != end) {
            if (*begin != '.') {
                int child = nodes[root_index].child[get_idx(begin)];
                if (child == TRIE_VOID_IDX) return false;
                root_index = child;
                begin++;
            } else {
                bool finded = false;
                begin++;
                for(int i = 0; i < sym_n; i ++) {
                    int child = nodes[root_index].child[i];
                    if (child != TRIE_VOID_IDX) {
                        finded = check(child, begin, end);
                    }
                    if (finded) {
                        return true;
                    }
                }
                return false;
            }
        }
        return nodes[root_index].val != TRIE_VOID_VAL;
    }

    void print() {
        for (int i = 0; i < nodes.size(); i++) {
            std::printf("node id: %d, index: %d, child:", i, nodes[i].val);
            for (int j = 0; j < sym_n; j++) {
                std::printf("%d ", nodes[i].child[j]);
            }
            std::printf("\n");
        }
    }
};
}  // namespace contest
