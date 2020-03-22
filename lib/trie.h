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

}  // namespace contest
