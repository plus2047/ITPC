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
const int N_MAX = 128;
int N, M, P;
int graph[N_MAX][N_MAX];
double average[N_MAX];
const int INF = 1E6;

void floyd() {
    rep(k, N) rep(i, N) rep(j, N) {
        graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
    }
}

void solve(int _turn) {
    scanf("%d%d%d", &N, &M, &P);
    rep(i, N) rep(j, N) { graph[i][j] = INF; }
    rep(i, N) { graph[i][i] = 0; }
    rep(i, M) {
        int U, V, D;
        scanf("%d%d%d", &U, &V, &D);
        graph[U - 1][V - 1] = D;
        graph[V - 1][U - 1] = D;
    }
    floyd();

    rep(i, N) {
        average[i] = 0;
        rep(j, N) { average[i] += graph[i][j]; }
        average[i] /= N - 1;
    }

    vector<double> pos(N, 0.), _pos(N, 0.);  // possibility
    pos[0] = 1;
    double total = 0;
    for (int i = 0; i < 100 and P > 0; i++, P--) {
        rep(i, N) { total += pos[i] * average[i]; }
        fill(allof(_pos), 0.);
        rep(i, N) rep(j, N) {
            if (i != j) {
                _pos[i] += pos[j] / (N - 1);
            }
        }
        swap(pos, _pos);
    }
    total += 1.0 * P * accumulate(average, average + N, 0.) / N;

    printf("Case #%d: %lf\n", _turn, total);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
