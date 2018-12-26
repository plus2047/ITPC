// for programing contest
#include <algorithm>
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
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#ifdef __APPLE__
#include "lib/show.h"
using namespace contest;
#endif

vector<int> fib;
vector<bool> first_win;
const int MAXN = 10000 + 10;
vector<bool> cache;
#define HASH(a, b) ((a)*MAXN + (b))

void init() {
    fib = {1, 2};
    while (fib.back() < MAXN) {
        fib.push_back(*(fib.rbegin()) + *(fib.rbegin() + 1));
    }
    fib.pop_back();

    first_win.resize(MAXN);
    first_win[0] = false;
    for (int i = 1; i < MAXN; i++) {
        bool win = false;
        for (int j = 0; j < fib.size(); j++) {
            int t = i - fib[j];
            if (t < 0) break;
            if (!first_win[t]) {
                win = true;
                break;
            }
        }
        first_win[i] = win;
    }
}

bool must_win(int a, int b) {
    if (!first_win[a] && !first_win[b]) return false;
    if (!first_win[a] || !first_win[b]) return true;
    bool win = false;
    for (int i = 0; i < fib.size(); i++) {
        int _a = a - fib[i];
        if (_a >= 0 && !must_win(_a, b)) win = true;
        int _b = b - fib[i];
        if (_b >= 0 && !must_win(a, _b)) win = true;
        if (_a < 0 && _b < 0) break;
    }
    return win;
}

int main() {
#ifdef __APPLE__
    freopen("_debug.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    init();
    // show("first_win: ", first_win.begin(), first_win.begin() + 100);
    // show("fib: ", fib.begin(), fib.end());
    int a, b;
    auto t0 = clock();
    while (scanf("%d%d", &a, &b) != EOF) {
        bool res = must_win(a, b);
        if (res) {
            printf("Xiaoai Win\n");
        } else {
            printf("Xiaobing Win\n");
        }
    }
    auto t1 = clock();
    printf("time cost: %lf\n", (t1 - t0) * 1.0 / CLOCKS_PER_SEC);
}