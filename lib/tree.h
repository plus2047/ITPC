#pragma once
#include <cstdlib>

namespace contest {
typedef int Val;
struct BinNode {  // Binary Search Tree Node
    BinNode *left = NULL, *right = NULL;
    Val val = 0;
    BinNode(Val _val) : val(_val) {}
};

BinNode* insert(BinNode* root, Val val) {
    while (true) {
        if (root->val == val) return NULL;
        BinNode** p_next = &(root->val > val ? root->left : root->right);
        if (*p_next == NULL) return *p_next = new BinNode(val);
        root = *p_next;
    }
}
}  // namespace contest
