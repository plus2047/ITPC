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
int count_group(vector<int>& nums) {
    int cnt = nums.front() != nums.back();
    rep(i, len(nums) - 1) {
        if (nums[i] != nums[i + 1]) {
            cnt++;
        }
    }
    return cnt;
}

void color_group(vector<int>& res, vector<int>& nums, int curr) {
    int n = len(nums);
    rep(i, n) {
        res[i] = curr;
        if (i != n - 1 and nums[i] != nums[i + 1]) {
            curr = curr != 1 ? 1 : 2;
        }
    }
}

void adjust(vector<int>& nums) {
    if (nums.front() == nums.back()) {
        rep(i, len(nums)) {
            if (nums[i + 1] != nums[0]) {
                nums[i] = -1;
                break;
            }
        }
    } else {
        rep(i, len(nums)) {
            if ((i == 0 or nums[i] != nums[i - 1]) and nums[i] == nums[i + 1]) {
                nums[i] = -1;
                break;
            }
        }
    }
}

// ========== contest code ==========
void solve(int _turn) {
    // KEEP CALM AND CARRY ON!
    int n;
    scanf("%d", &n);
    vector<int> nums(n);
    rep(i, n) { scanf("%d", &nums[i]); }

    vector<int> res(n);
    int n_group = count_group(nums);
    if (n_group == 0) {
        fill(allof(res), 1);
    } else if (n_group == len(nums) and n_group % 2 == 1) {
        color_group(res, nums, 3);
    } else if (n_group % 2 == 1) {
        adjust(nums);
        color_group(res, nums, 2);
    } else {
        color_group(res, nums, 2);
    }

    printf("%d\n", *max_element(allof(res)));
    rep(i, n) { printf("%d ", res[i]); }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
