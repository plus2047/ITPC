#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

namespace contest {

struct Treap {
    typedef long long int TreeKey;
    typedef int HeapKey;
    typedef int Count;
    const static TreeKey TREE_KEY_ZERO = 0LL;
    const static Count COUNT_ZERO = 0;

    struct Node {
        Node *left, *right;

        // independent fields
        TreeKey tree_key;
        HeapKey heap_key;
        Count node_count;
        // add val field if necessary.
        // Val val;

        // calculated fields
        // the fields below should be calculated by fields above.
        TreeKey tree_key_sum;
        Count count_sum;
    };

    inline Count _get_node_count(Node* node) {
        return node ? node->node_count : COUNT_ZERO;
    }
    inline Count _get_count_sum(Node* node) {
        return node ? node->count_sum : COUNT_ZERO;
    }
    inline TreeKey _get_tree_key(Node* node) {
        return node ? node->tree_key * node->node_count : TREE_KEY_ZERO;
    }
    inline TreeKey _get_tree_key_sum(Node* node) {
        return node ? node->tree_key_sum : TREE_KEY_ZERO;
    }

    // using independent fields and childs
    // to update calculated fields
    inline void _update_node(Node* node) {
        node->tree_key_sum = _get_tree_key(node) +
                             _get_tree_key_sum(node->left) +
                             _get_tree_key_sum(node->right);

        node->count_sum = _get_node_count(node) + _get_count_sum(node->left) +
                          _get_count_sum(node->right);
    }

    inline Node* _init_node() {
        Node* node = _new_node();
        node->left = node->right = NULL;
        node->tree_key = added_tree_key;
        node->heap_key = added_heap_key;
        node->node_count = added_count;
        _update_node(node);
        return node;
    }

    inline void _to_string(Node* node, char* buff) {
        sprintf(buff,
                "<tree key: %lld, count: %d, tree key sum: %lld, count "
                "sum: %d>",
                node->tree_key, node->node_count, node->tree_key_sum,
                node->count_sum);
    }

    // if added new independent field, add it here.
    TreeKey added_tree_key;
    HeapKey added_heap_key;
    Count added_count;

    // ================================================================
    // public methods
    inline void add(TreeKey tree_key, int count) {
        added_tree_key = tree_key;
        added_heap_key = rand();
        added_count = count;
        root = _insert(root);
    }

    TreeKey get_prefix_sum(Node* node, TreeKey key) {
        // prefix sum (included)
        if (not node) {
            return TREE_KEY_ZERO;
        }

        if (key > node->tree_key) {
            return _get_tree_key(node) + _get_tree_key_sum(node->left) +
                   get_prefix_sum(node->right, key);
        } else if (key < node->tree_key) {
            return get_prefix_sum(node->left, key);
        } else {
            return _get_tree_key(node) + _get_tree_key_sum(node->left);
        }
    }

    Count get_prefix_count(Node* node, TreeKey key) {
        // prefix count (included)
        if (not node) {
            return COUNT_ZERO;
        }

        if (key > node->tree_key) {
            return _get_node_count(node) + _get_count_sum(node->left) +
                   get_prefix_count(node->right, key);
        } else if (key < node->tree_key) {
            return get_prefix_count(node->left, key);
        } else {
            return _get_node_count(node) + _get_count_sum(node->left);
        }
    }

    Node* get_node_by_idx(Node* node, Count idx) {
        // get node index (o-indexed)
        Count left_count = _get_count_sum(node->left);

        if (left_count == idx) {
            return node;
        } else if (left_count > idx) {
            return get_node_by_idx(node->left, idx);
        } else {
            return get_node_by_idx(node->right,
                                   idx - left_count - node->node_count);
        }
    }

    // ================================================================
    // usually donot need to modify below.
    // if you want to remember it, go below and remenber the rotate logic.

    Node* root = NULL;

    // object pool
    const int ObjectFrame = 1024;
    Node* obj_pool;
    int obj_pool_bias = 0;
    vector<Node*> obj_frames;

    inline Node* _new_node() {
        if (obj_pool_bias >= ObjectFrame) {
            obj_frames.push_back(obj_pool = new Node[ObjectFrame]);
            obj_pool_bias = 0;
        }
        Node* p = obj_pool + obj_pool_bias++;
        return p;
    }

    /*    y                          x
         / \     Right Rotation     /  \
        x   T3   – – – – – – – >   T1   y
       / \       < - - - - - - -       / \
      T1  T2     Left Rotation       T2  T3
      https://www.geeksforgeeks.org          */

    Node* _right_rotate(Node* y) {
        Node *x = y->left, *T2 = x->right;

        x->right = y;
        y->left = T2;

        _update_node(x);
        _update_node(y);

        return x;
    }

    Node* _left_rotate(Node* x) {
        Node *y = x->right, *T2 = y->left;

        y->left = x;
        x->right = T2;

        _update_node(x);
        _update_node(y);

        return y;
    }

    Node* _insert(Node* node) {
        if (not node) {
            return _init_node();
        }

        if (added_tree_key < node->tree_key) {
            node->left = _insert(node->left);
            if (node->left->heap_key > node->heap_key) {
                node = _right_rotate(node);
            }

        } else if (added_tree_key > node->tree_key) {
            node->right = _insert(node->right);
            if (node->right->heap_key > node->heap_key) {
                node = _left_rotate(node);
            }

        } else {
            node->node_count += added_count;
        }

        _update_node(node);
        return node;
    }

    void print() { _print(root, 0); }
    void _print(Node* node, int depth) {
        static char buff[1024];

        if (not node) return;
        _print(node->left, depth + 1);

        for (int i = 0; i < depth; i++) printf("  ");
        _to_string(node, buff);
        printf("%s\n", buff);

        _print(node->right, depth + 1);
    }

    Treap() { obj_frames.push_back(obj_pool = new Node[ObjectFrame]); };
    ~Treap() {
        for (auto p : obj_frames) {
            delete[] p;
        }
    }
};

}  // namespace contest
