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
#define vec2d(type, name, m, n, v) \
    vector<vector<type>> name = vector<vector<type>>(m, vector<type>(n, v))

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

// min_opt(right): min opt to get substr [0, right]
// id(left, right): id(a, b) == id(c, d) if [a, b] == [c, d]
// min_opt(right, id): min opt to get [0, right] with clipboard substr with id
// remain.

// min_opt(right) = min_{id} min_opt(right, id)
// min_opt(right, id) = min(
//   min_opt(right - 1, id),
//   min_{id} min_opt(id, right - N) + 2 if tail is id
//   min_opt(id, right - N) + 1 if tail is id
// )

const int L_MAX = 128;
char buff[L_MAX];
string s;
int length;

const int ID_MAX = L_MAX * L_MAX;
int id[L_MAX][L_MAX];
int id_end;
int id_size[ID_MAX];
int first[ID_MAX];

int min_opt_all[L_MAX];
int min_opt[L_MAX][ID_MAX];

inline void get_id_and_first() {
    unordered_map<string, int> m;
    m[""] = 0;
    id_size[0] = 0;
    first[0] = 0;
    rep(left, length) repr(right, left, length) {
        string sub = s.substr(left, right - left + 1);
        int _id = len(m);
        if (m.count(sub)) {
            _id = m[sub];
        } else {
            m[sub] = _id;
            id_size[_id] = right - left + 1;
            first[_id] = left;
        }
        id[left][right] = _id;
    }
    id_end = len(m);
}

inline void get_min_opt() {
    int INF = length * 2;
    min_opt_all[0] = min_opt[0][0] = 1;
    repr(i, 1, id_end) { min_opt[0][i] = INF; }
    repr(right, 1, length) {
        int min_all = INF;
        rep(_id, id_end) {
            int& r = min_opt[right][_id];
            int c_size = id_size[_id];
            int tail_left = right - c_size + 1;
            // just append
            r = min_opt[right - 1][_id] + 1;
            // if str(id) is tail
            if (c_size != 0 and tail_left > 0 and
                id[tail_left][right] == _id and
                first[_id] + c_size <= tail_left) {
                r = min(r, min_opt[tail_left - 1][_id] + 1);
                r = min(r, min_opt_all[tail_left - 1] + 2);
            }
            asmin(min_all, r);
        }
        min_opt_all[right] = min_all;
    }
}

void solve(int _turn) {
    scanf("%s", buff);
    s = buff;
    length = len(s);

    get_id_and_first();
    get_min_opt();

    // show("min_opt_all: ", min_opt_all, min_opt_all + length);
    printf("Case #%d: %d\n", _turn, min_opt_all[length - 1]);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
