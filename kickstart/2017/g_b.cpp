// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

#include <array>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
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

#undef __LOCAL__

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
const int N_MAX = 128;
int N, R[N_MAX], B[N_MAX];

int find(vector<int>& ufs, int i) {
    return ufs[i] == i ? i : ufs[i] = find(ufs, ufs[i]);
}
void update(vector<int>& ufs, int i, int j) {
    ufs[find(ufs, i)] = find(ufs, j);
}

void solve(int _turn) {
    // CONTEST BEGIN!!!
    scanf("%d", &N);
    rep(i, N) { scanf("%d", &R[i]); }
    rep(i, N) { scanf("%d", &B[i]); }

    // min spanning tree
    typedef tuple<int, int, int> Edge;  // <length, nod1, node2>
    vector<Edge> edges;
    rep(i, N) range(j, i + 1, N - 1) {
        edges.push_back({min(R[i] ^ B[j], R[j] ^ B[i]), i, j});
    }
    sort(allof(edges));

    vector<int> ufs(N);
    rep(i, N) { ufs[i] = i; }
    lld total = 0;

    for (auto& e : edges) {
        int x, n1, n2;
        tie(x, n1, n2) = e;
        if (find(ufs, n1) != find(ufs, n2)) {
            update(ufs, n1, n2);
            total += lld(x);
        }
    }

    printf("Case #%d: %lld\n", _turn, total);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
