// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// #undef __LOCAL__

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

#include <map>
#include <queue>
#include <set>
#include <stack>
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

// ===== personal contest env =====

typedef long long int lld;

#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)

#define iter(i, begin, end) \
    for (int i = begin, d = begin < end ? 1 : -1; i != end; i += d)
#define each(i, first, last) \
    for (int i = first, d = first < last ? 1 : -1; i != last + d; i += d)

#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define rev(i, N) for (int i = int(N) - 1; i >= 0; --i)

#if __cplusplus >= 201103L
template <typename num>
using mat = vector<vector<num> >;

template <typename num>
inline mat<num> make_mat(int s1, int s2, num val) {
    return mat<num>(s1, vector<num>(s2, val));
}

template <typename num>
inline void fill(mat<num>& m, num val) {
    for (auto& v : m)
        for (auto& n : v) n = val;
}

template <typename num>
void show(mat<num> m) {
    for (const auto& v : m) {
        for (const auto& n : v) cout << n << ' ';
        cout << endl;
    }
}
#endif  // C++11

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
// This solution is good enough. But it cannot pass POJ.
struct State {
    int x1, x2, step;
};

int P;
set<pair<int, int> > seen;
deque<State> que;

void push(int x1, int x2, int step) {
    if (x1 < x2) swap(x1, x2);
    if (x1 == x2 or seen.count({x1, x2})) return;
    seen.insert({x1, x2});
    que.push_back({x1, x2, step});
}

// ===== kickstart template =====
int main() {
    while (scanf("%d", &P) != EOF) {
        if (P <= 1) {
            printf("1\n");
            continue;
        }
        seen.clear();
        que.clear();
        push(1, 0, 0);
        int res = -1;

        while (que.size()) {
            State s = que.front();
            que.pop_front();
            int x1 = s.x1, x2 = s.x2, step = s.step;
            step++;
            if (x1 + x2 == P or x1 * 2 == P or x2 * 2 == P or
                abs(x1 - x2) == P) {
                res = step;
                break;
            }
            push(x1 + x2, x1, step);
            push(x1 + x2, x2, step);
            push(x1 * 2, x1, step);
            push(x1 * 2, x2, step);
            push(x2 * 2, x1, step);
            push(x2 * 2, x2, step);
            push(abs(x1 - x2), x1, step);
            push(abs(x1 - x2), x2, step);
        }

        cout << res << endl;
    }
}
