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
char get_pos(int pos) {
    printf("%d\n", pos + 1);
    // fprintf(stderr, "%d\n", pos + 1);
    fflush(stdout);
    static char inp[64];
    scanf("%s", inp);
    return inp[0];
}

void complement(string& s) {
    for (char& c : s) {
        c = c == '0' ? '1' : '0';
    }
}

int main() {
    int T, B;
    scanf("%d%d", &T, &B);
    // fprintf(stderr, "%d %d\n", T, B);
    // fflush(stderr);
    rep(t, T) {
        string res(B, '0');
        int left = 0, right = B - 1;
        int eq_left = -1, eq_right = -1, neq_left = -1, neq_right = -1;
        char inp_left, inp_right;
        const int QUERY_NUM = 150;

        for (int i = 1; i <= QUERY_NUM; i += 2) {
            if (i != 1 and i % 10 == 1) {
                if (eq_left == -1) {
                    // all pair diff.
                    inp_left = get_pos(neq_left);
                    inp_right = get_pos(neq_right);
                } else if (neq_left == -1) {
                    // all pair same.
                    inp_left = get_pos(eq_left);
                    inp_right = get_pos(eq_right);
                } else {
                    inp_left = get_pos(eq_left);
                    inp_right = get_pos(neq_right);
                }
                if (eq_left != -1 and inp_left != res[eq_left]) {
                    complement(res);
                }
                if (neq_right != -1 and inp_right != res[neq_right]) {
                    reverse(allof(res));
                }
                i += 2;
            }

            inp_left = get_pos(left);
            inp_right = get_pos(right);

            if (eq_left == -1 and inp_left == inp_right) {
                eq_left = left, eq_right = right;
            }
            if (neq_left == -1 and inp_left != inp_right) {
                neq_left = left, neq_right = right;
            }

            if (left <= right) {
                res[left] = inp_left;
                res[right] = inp_right;
                left++, right--;
            }
        }

        printf("%s\n", res.c_str());
        // fprintf(stderr, "%s\n", res.c_str());
        fflush(stdout);
        char buff[64];
        scanf("%s", buff);
        if (buff[0] == 'N') {
            break;
        }
    }
}
