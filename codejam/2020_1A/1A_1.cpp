// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// #undef __LOCAL__

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
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
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

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
char buff[128];

vector<string> split(string& s) {
    string t;
    vector<string> res;
    for (char c : s) {
        if (c == '*') {
            res.push_back(t);
            t.clear();
        } else {
            t.push_back(c);
        }
    }
    res.push_back(t);
    return res;
}

string get_pre(vector<string>& pre_vec) {
    string res;
    for (int i = 0;; i++) {
        char c = 0;
        for (string s : pre_vec) {
            if (i < len(s)) {
                if (c == 0) {
                    c = s[i];
                } else if (c != s[i]) {
                    res = "*";
                    c = 0;
                    break;
                }
            }
        }
        if (c == 0) {
            break;
        } else {
            res.push_back(c);
        }
    }
    return res;
}

string get_suf(vector<string>& suf_vec) {
    for(string& s: suf_vec) {
        reverse(allof(s));
    }
    string r = get_pre(suf_vec);
    reverse(allof(r));
    for(string& s: suf_vec) {
        reverse(allof(s));
    }
    return r;
}

void solve(int _turn) {
    int N;
    scanf("%d", &N);
    vector<string> patterns(N);
    rep(i, N) {
        scanf("%s", buff);
        patterns[i] = buff;
    }
    vector<string> pre, suf, contain;
    rep(i, N) {
        string& p = patterns[i];
        vector<string> sp = split(p);
        pre.push_back(sp.front());
        suf.push_back(sp.back());
        contain.insert(contain.end(), next(sp.begin()), prev(sp.end()));
    }


    string pre_s = get_pre(pre);
    string suf_s = get_suf(suf);

    // show("pre: ", allof(pre));
    // show("suf: ", allof(suf));
    // cout << "pre: " << pre_s << endl;
    // cout << "suf: " << suf_s << endl;

    string res;
    if (pre_s != "*" and suf_s != "*") {
        res = pre_s;
        for (string s : contain) {
            res += s;
        }
        res += suf_s;
    } else {
        res = "*";
    }
    printf("Case #%d: %s\n", _turn + 1, res.c_str());
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
