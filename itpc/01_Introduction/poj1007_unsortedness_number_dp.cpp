// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <sstream>

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
char strs[128][64];
int n, m;

int get_unsortedness(int i) {
    static int cnt[26];
    rep(j, 26) { cnt[j] = 0; }

    char* s = strs[i];
    int total = 0;
    rep(k, n) {
        int ord = s[k] - 'A';
        range(j, ord + 1, 25) { total += cnt[j]; }
        cnt[ord]++;
    }

    return total;
}

// ===== kickstart template =====
int main() {
    scanf("%d%d", &n, &m);
    rep(i, m) { scanf("%s", strs[i]); }
    vector<pair<int, int> > w;
    rep(i, m) { w.push_back({get_unsortedness(i), i}); }
    sort(allof(w));
    rep(i, m) { printf("%s\n", strs[w[i].second]); }
}
