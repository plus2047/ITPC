#pragma once
#include <cstdlib>

namespace contest {
typedef int Val;
struct TNode {
    TNode *left = NULL, *right = NULL;
    Val val = 0;
    TNode(Val _val) : val(_val) {}
};

TNode* insert(TNode* root, Val val) {
    while (true) {
        if (root->val == val) return NULL;
        TNode** p_next = &(root->val > val ? root->left : root->right);
        if (*p_next == NULL) return *p_next = new TNode(val);
        root = *p_next;
    }
}
}  // namespace contest
