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
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int LL;
#define G(_tuple, num) (get<num>(_tuple))
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)

template <int group = 20, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    cout << note;
    for (int i = 1; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0 or begin == end) std::cout << std::endl;
    }
#endif  // __LOCAL__
}

#ifdef __LOCAL__
std::clock_t _t0 = 0;
void timer_begin() { _t0 = clock(); }
void timer_end(const char* note) {
    double delta = double(clock() - _t0) / CLOCKS_PER_SEC;
    printf("%s cost: %lf sec.\n", note, delta);
}
#else
#define timer_begin() (void(0))
#define timer_end(note) (void(0))
#endif  // __LOCAL__

// ===== personal contest template =====

// ========== contest code ==========
void solve(int _turn) {
    int R, C;
    scanf("%d%d", &R, &C);
    vector<string> graph(R);
    rep(i, R) cin >> graph[i];

    vector<vector<int>> dis(R, vector<int>(C, R + C));
    queue<tuple<int, int, int>> que;
    rep(i, R) rep(j, C){
        if(graph[i][j] == '1'){
            dis[i][j] = 1;
            que.push({0, i, j});
        }
    }
    if(que.size() == 0){
        printf("Case #%d: %d\n", _turn, (R + C) / 2);
        return;
    }
    vector<tuple<int, int, int>> points;
    while(!que.empty()){
        int d, i, j;
        tie(d, i, j) = que.front();
        que.pop(); d++;
        if(i != 0 and dis[i - 1][j] > d){
            dis[i - 1][j] = d;
            que.push({d, i - 1, j});
            points.push_back({d, i - 1, j});
        }
        if(j != 0 and dis[i][j - 1] > d){
            dis[i][j - 1] = d;
            que.push({d, i, j - 1});
            points.push_back({d, i, j - 1});
        }
        if(i != R - 1 and dis[i + 1][j] > d){
            dis[i + 1][j] = d;
            que.push({d, i + 1, j});
            points.push_back({d, i + 1, j});
        }
        if(j != C - 1 and dis[i][j + 1] > d){
            dis[i][j + 1] = d;
            que.push({d, i, j + 1});
            points.push_back({d, i, j + 1});
        }
    }
    if(points.size() == 0){
        printf("Case #%d: %d\n", _turn, 0);
        return;
    }
    int maxd = G(points.back(), 0);
    
    int NP = points.size();
    repi(p, NP){
        int d = 0, i, j;
        i = G(points[p], 1);
        j = G(points[p], 2);
        repi(q, NP){
            if(G(points[q], 0) <= d) break;
            int nd = abs(i - G(points[q], 1)) + abs(j - G(points[q], 2));
            if(d < nd) d = nd;
        }
        if(d < maxd) maxd = d;
    }
    printf("Case #%d: %d\n", _turn, maxd);
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in building command.
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
