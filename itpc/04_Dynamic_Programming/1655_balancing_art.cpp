// ===== programing contest template ======
// ===== using a very very old C++ version =====

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int lld;
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define range(i, left, right) for (int i = int(left); i <= int(right); ++i)
#define irange(i, left, right) for (int i = int(right); i >= int(left); --i)

// #undef __LOCAL__

template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void echo(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ===== personal contest template =====

// ========== contest code ==========

int main() {
    int T, N;
    scanf("%d", &T);
    rep(t, T) {
        scanf("%d", &N);

        vector<vector<int> > graph(N);
        rep(_, N - 1) {
            int i, j;
            scanf("%d%d", &i, &j);
            graph[i - 1].push_back(j - 1);
            graph[j - 1].push_back(i - 1);
        }

        vector<int> topo;
        vector<int> parent(N, -1);
        topo.push_back(0);
        parent[0] = 0;
        int curr = 0;
        while (curr < len(topo)) {
            int n = topo[curr++];
            rep(i, len(graph[n])) {
                int child = graph[n][i];
                if (parent[child] != -1) continue;
                topo.push_back(child);
                parent[child] = n;
            }
        }
        reverse(allof(topo));
        show("topo: ", allof(topo));
        show("parent: ", allof(parent));

        vector<int> subtree_size(N, 1);
        rep(i, N - 1) {
            int n = topo[i], p = parent[n];
            subtree_size[p] += subtree_size[n];
        }
        show("subtree size: ", allof(subtree_size));

        vector<int> max_child_tree_size(N, 0);
        rep(i, N - 1) {
            int n = topo[i], p = parent[n];
            int& v = max_child_tree_size[p];
            v = max(v, subtree_size[n]);
        }
        show("max child tree size: ", allof(max_child_tree_size));

        vector<int> balance(N, 0);
        rep(i, N) {
            int n = topo[i];
            int& v = balance[n];
            v = max(N - subtree_size[n], max_child_tree_size[n]);
        }

        int idx = -1, b = N;
        rep(i, N) {
            if (balance[i] < b) {
                idx = i;
                b = balance[i];
            }
        }
        printf("%d %d\n", idx + 1, b);
        fflush(stdout);
    }
}
