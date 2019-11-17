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
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i++)

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

// ===== personal contest template =====

// ========== contest code ==========
int L;

bool anag_find(string& str, vector<int> cnt, int type) {
    for (int left = 0, right = 0; right < L; right++) {
        int& c = cnt[str[right] - 'A'];
        if ((--c) == 0) {
            if ((--type) == 0) return true;
        }
        while (c < 0) {
            if(cnt[str[left++] - 'A']++ == 0) type++;
        }
    }
    return false;
}

void solve(int _turn) {
    scanf("%d", &L);
    string A, B;
    cin >> A >> B;
    int res = 0;
    vector<int> cnt(26);
    for (int leftA = 0; leftA < L; leftA++) {
        fill(allof(cnt), 0);
        int type = 0;
        for (int rightA = leftA; rightA < L; rightA++) {
            if (cnt[A[rightA] - 'A']++ == 0) type++;
            res += anag_find(B, cnt, type);
            // printf("leftA: %d, rightA: %d, type: %d, res: %d\n", leftA, rightA, type, res);
            // show("cnt: ", allof(cnt));
        }
    }
    printf("Case #%d: %d\n", _turn, res);
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
