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
#define asmax(m, update) \
    if (m < update) m = update;
#define asmin(m, update) \
    if (m > update) m = update;

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
    string str;
    cin >> str;
    int N = str.size();
    vector<string> part(1);
    vector<int> idx(N);
    for(int i = 0; i < N; i++) {
        if(str[i] == '_') {
            if(part.back().size() != 0){
                part.push_back("");
            }
            idx[i] = part.size() - 1;
        } else {
            part.back().push_back(str[i]);
        }
    }
    // show("part: ", allof(part));
    // show("idx: ", allof(idx));
    for(int i = 0; i < N; i++) {
        if(str[i] == '_') {
            int next_idx = idx[i];
            if(next_idx != 0 and part[next_idx] == part[next_idx - 1]) {
                str[i] = '+';
            }
        }
    }
    cout << str << endl;
}

// ===== kickstart template =====
int main() {
    int T = 4;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
