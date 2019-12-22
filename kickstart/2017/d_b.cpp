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

#undef __LOCAL__

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
vector<lld> get_sum(vector<lld>& vec, int k) {
    int n = len(vec);
    vector<pair<lld, int>> pre(n + 1);
    rep(i, n) {
        pre[i + 1].first = pre[i].first + vec[i];
        pre[i + 1].second = i + 1;
    }
    sort(allof(pre));
    vector<lld> res;
    priority_queue<lld> pq;
    rep(left, n) irange(right, left + 1, n) {
        if (pre[right].second < pre[left].second) continue;
        int x = pre[right].first - pre[left].first;
        if (len(pq) >= k and x <= -pq.top()) break;
        pq.push(-x);
        while (len(pq) > k) pq.pop();
    }
    while (len(pq)) {
        res.push_back(-pq.top());
        pq.pop();
    }
    rep(left, n) irange(right, left + 1, n) {
        if (pre[right].second > pre[left].second) continue;
        int x = pre[left].first - pre[right].first;
        if (x == 0) break;  // just process zero one time.
        if (len(pq) >= k and x >= pq.top()) break;
        pq.push(x);
        while (len(pq) > k) pq.pop();
    }
    while (len(pq)) {
        res.push_back(pq.top());
        pq.pop();
    }
    sort(allof(res));
    return res;
}

lld get_multiply(vector<lld>& a, vector<lld>& b, int k) {
    typedef tuple<lld, int, int> Key;
    priority_queue<Key> pq;
    int n1 = len(a), n2 = len(b);
    rep(i, n1) {
        int j = a[i] >= 0 ? n2 - 1 : 0;
        pq.push({a[i] * b[j], i, j});
    }
    lld x = 0;
    int i = 0, j = 0;
    echo("multiply: ");
    while(k--) {
        tie(x, i, j) = pq.top();
        pq.pop();
        echo("%lld ", x);
        j += a[i] >= 0 ? -1 : 1;
        if(j >= 0 and j < n2) pq.push({a[i] * b[j], i, j});
    }
    echo("\n");
    return x;
}

void solve(int _turn) {
    lld n, k, c, d, e1, e2, f;
    scanf("%lld%lld", &n, &k);
    vector<lld> a(n), b(n), x(n), y(n), r(n), s(n);
    scanf("%lld%lld%lld%lld%lld%lld%lld", &a[0], &b[0], &c, &d, &e1, &e2, &f);

    // init data ====
    x[0] = a[0], y[0] = b[0], r[0] = s[0] = 0;
    range(i, 1, n - 1) {
        x[i] = (c * x[i - 1] + d * y[i - 1] + e1) % f;
        y[i] = (d * x[i - 1] + c * y[i - 1] + e2) % f;
        r[i] = (c * r[i - 1] + d * s[i - 1] + e1) % 2;
        s[i] = (d * r[i - 1] + c * s[i - 1] + e2) % 2;
        a[i] = r[i] ? -x[i] : x[i];
        b[i] = s[i] ? -y[i] : y[i];
    }
    echo("\n");
    show("a: ", allof(a));
    show("b: ", allof(b));

    vector<lld> sum_a = get_sum(a, k);
    vector<lld> sum_b = get_sum(b, k);
    show("sum_a: ", allof(sum_a));
    show("sum_b: ", allof(sum_b));

    lld res = get_multiply(sum_a, sum_b, k);

    printf("Case #%d: %lld\n", _turn, res);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
