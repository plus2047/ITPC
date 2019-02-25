// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== persional contest env =====

typedef long long int LL;
typedef long long unsigned LLU;
typedef long double LD;
#define G(_tuple, num) (get<num>(_tuple))
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
    printf("%s", note);
    while (begin != end) {
        std::cout << *(begin++) << ' ';
    }
    std::cout << std::endl;
}

template <typename ITER>
void show(const char* note, ITER begin, ITER end, int group) {
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
}
struct MergeFindSet {
    std::vector<int> p;
    MergeFindSet(int n) : p(n) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int x, int y) { p[find(y)] = find(x); }
};

// ========== contest code ==========
vector<vector<int>> graph;
int circle_begin, circle_end;
vector<int> res;
vector<bool> seen;

bool mark_circle(int idx) {
    seen[idx] = true;
    if (idx == circle_end) {
        res[idx] = 0;
        return true;
    }
    for (int child : graph[idx]) {
        if (seen[child]) continue;
        if (mark_circle(child)) {
            res[idx] = 0;
            return true;
        }
    }
    return false;
}

void solve(int _turn) {
    int N;
    scanf("%d", &N);
    graph = vector<vector<int>>(N);
    MergeFindSet mfs(N);
    rep(i, N) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--, y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
        if (mfs.find(x) == mfs.find(y)) {
            circle_begin = x, circle_end = y;
        } else {
            mfs.merge(x, y);
        }
    }
    seen = vector<bool>(N, false);
    res = vector<int>(N, -1);
    mark_circle(circle_begin);
    // show("after mark circle: ", allof(res));

    deque<int> deq;
    fill(allof(seen), false);
    rep(i, N) {
        if (res[i] == 0) {
            seen[i] = true;
            deq.push_back(i);
        }
    }
    // show("seen: ", allof(seen));
    while (deq.size()) {
        int node = deq.front();
        deq.pop_front();
        for (int child : graph[node]) {
            if (seen[child]) continue;
            seen[child] = true;
            res[child] = res[node] + 1;
            deq.push_back(child);
        }
    }
    printf("Case #%d:", _turn);
    rep(i, N) printf(" %d", res[i]);
    printf("\n");
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
