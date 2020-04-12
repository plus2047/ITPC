// ===== programing contest template ======

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#if __cplusplus >= 201103L
#include <array>
#include <bitset>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#endif  // C++11
using namespace std;

typedef long long int lld;
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

// ========== contest code ==========

struct Node {
    int val;
    Node *left, *right, *up, *down;
};

int R, C, N;
vector<Node> nodes;
inline int ord(int i, int j) { return i * C + j; }
inline Node* new_node(int val, int i, int j) {
    Node* node = &nodes[ord(i, j)];
    node->val = val;
    node->up = i == 0 ? nullptr : &nodes[ord(i - 1, j)];
    node->down = i == R - 1 ? nullptr : &nodes[ord(i + 1, j)];
    node->left = j == 0 ? nullptr : &nodes[ord(i, j - 1)];
    node->right = j == C - 1 ? nullptr : &nodes[ord(i, j + 1)];
    return node;
}

inline void remove(Node* node) {
    if (node->up and node->down) {
        node->up->down = node->down;
        node->down->up = node->up;
    } else if (node->up) {
        node->up->down = nullptr;
    } else if (node->down) {
        node->down->up = nullptr;
    }

    if (node->left and node->right) {
        node->left->right = node->right;
        node->right->left = node->left;
    } else if (node->left) {
        node->left->right = nullptr;
    } else if (node->right) {
        node->right->left = nullptr;
    }
}

set<Node*> update;
lld total;
void step() {
    static vector<Node*> _update;
    _update.clear();
    for (auto n : update) {
        // check if remove
        int nei_cnt = 0, nei_total = 0;
        if (n->up) nei_cnt++, nei_total += n->up->val;
        if (n->down) nei_cnt++, nei_total += n->down->val;
        if (n->left) nei_cnt++, nei_total += n->left->val;
        if (n->right) nei_cnt++, nei_total += n->right->val;

        if (n->val * nei_cnt < nei_total) {
            _update.push_back(n);
        }
    }

    for (auto n : _update) {
        total -= n->val;
        n->val = 0;
    }

    update.clear();
    for (auto n : _update) {
        if (n->up and n->up->val) update.insert(n->up);
        if (n->down and n->down->val) update.insert(n->down);
        if (n->left and n->left->val) update.insert(n->left);
        if (n->right and n->right->val) update.insert(n->right);
        remove(n);
    }
}

void solve(int _turn) {
    scanf("%d%d", &R, &C);
    N = R * C;
    nodes.resize(N);

    update.clear();
    total = 0;
    rep(i, R) rep(j, C) {
        int val;
        scanf("%d", &val);
        update.insert(new_node(val, i, j));
        total += val;
    }

    lld score = 0;
    while (update.size()) {
        // printf("total: %lld\n", total);
        score += total;
        step();
    }
    printf("Case #%d: %lld\n", _turn + 1, score);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
