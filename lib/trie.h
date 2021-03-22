#pragma once
#include <algorithm>
#include <string>

namespace contest {

const int CHAR_N = 26;
struct TrieNode {
    TrieNode* child[CHAR_N];
    // pre_cnt: count of strings with this node as prefix.
    // end_cnt: count of strings with this node as ending.
    int pre_cnt = 0, end_cnt = 0;
    TrieNode() { std::fill(child, child + CHAR_N, nullptr); }
};

void insert(TrieNode* node, std::string& str) {
    for (int i = 0; i < int(str.size()); i++) {
        int ci = str[i] - 'A';  // CHECK THIS!
        if (not node->child[ci]) {
            node->child[ci] = new TrieNode();
        }
        node = node->child[ci];
        node->pre_cnt++;
    }
    node->pre_cnt++;
    node->end_cnt++;
}

struct BinTrieNode {
    BinTrieNode *ch0, *ch1;
    int node_num;
};

template <typename BIN>
void insert(BinTrieNode* node, BIN val, BIN mask) {
    while (mask) {
        node->node_num++;
        BinTrieNode** child = &(val & mask ? node->ch1 : node->ch0);
        if (not *child) *child = new BinTrieNode({nullptr, nullptr, 0});
        node = *child;
        mask >>= 1;
    }
    node->node_num++;
}

template <typename BIN>
int leq(BinTrieNode* node, BIN bound, BIN inverse, BIN mask) {
    // count number x in the trie, s.t. x xor inverse <= bound
    int res = 0;
    while (mask and node) {
        BinTrieNode **ch0 = &node->ch0, **ch1 = &node->ch1;
        if (mask & inverse) swap(ch0, ch1);
        if (mask & bound) {
            res += *ch0 ? (*ch0)->node_num : 0;
            node = *ch1;
        } else {
            node = *ch0;
        }
        mask >>= 1;
    }
    res += node ? node->node_num : 0;
    return res;
}

}  // namespace contest
