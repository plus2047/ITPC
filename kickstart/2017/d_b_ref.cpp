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
#define REP(i, n) for (int i = 0; i < int(n); ++i)
#define REPE(i, a, b) for (int i = (a); i <= int(b); ++i)
#define SZ(x) ((int)(x).size())
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define EB emplace_back
using LL = long long;
using PII = pair<int, int>;
#define F first
#define S second

const int maxn = 100010;

int n, k, a1, b1, c, d, e1, e2, f;

LL x[maxn], y[maxn], r[maxn], s[maxn], a[maxn], b[maxn];

LL sa[maxn], sb[maxn];

vector<LL> gen(LL *a) {
    vector<LL> ps(n + 1);
    REPE(i, 1, n) { ps[i] = ps[i - 1] + a[i]; }
    vector<pair<LL, int>> v;
    REPE(i, 0, n) v.EB(ps[i], i);
    sort(ALL(v));
    priority_queue<LL> q1;                           // <= 0
    priority_queue<LL, vector<LL>, greater<LL>> q2;  // > 0
    int m = v.size();
    for (int i = m - 1; i >= 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (v[i].S < v[j].S) continue;
            LL t = v[i].F - v[j].F;
            if (t <= 0) break;
            if (q2.size() >= k && t <= q2.top()) break;
            q2.push(t);
            while (q2.size() > k) q2.pop();
        }
    }
    REP(i, m) {
        for (int j = m - 1; j > i; --j) {
            if (v[i].S < v[j].S) continue;
            LL t = v[i].F - v[j].F;
            if (t > 0) break;
            if (q1.size() >= k && t >= q1.top()) break;
            q1.push(t);
            while (q1.size() > k) q1.pop();
        }
    }
    vector<LL> ret;
    while (q1.size()) {
        ret.push_back(q1.top());
        q1.pop();
    }
    while (q2.size()) {
        ret.push_back(q2.top());
        q2.pop();
    }
    sort(ALL(ret));
    return ret;
}

vector<LL> proc(LL *a) {
    LL ps = 0;
    multiset<LL> ms;
    priority_queue<LL> q1;                           // <= 0
    priority_queue<LL, vector<LL>, greater<LL>> q2;  // > 0
    ms.insert(0);
    REPE(i, 1, n) {
        ps += a[i];
        for (auto it : ms) {
            LL t = ps - it;
            if (t <= 0) break;
            if (q2.size() >= k && t <= q2.top()) break;
            q2.push(t);
            while (q2.size() > k) q2.pop();
        }
        for (auto it = ms.rbegin(); it != ms.rend(); ++it) {
            LL t = ps - *it;
            if (t > 0) break;
            if (q1.size() >= k && t >= q1.top()) break;
            q1.push(t);
            while (q1.size() > k) q1.pop();
        }
        ms.insert(ps);
    }
    vector<LL> ret;
    while (q1.size()) {
        ret.push_back(q1.top());
        q1.pop();
    }
    while (q2.size()) {
        ret.push_back(q2.top());
        q2.pop();
    }
    sort(ALL(ret));
    return ret;
}

void solve() {
    scanf("%d%d%d%d%d%d%d%d%d", &n, &k, &a1, &b1, &c, &d, &e1, &e2, &f);
    x[1] = a1, y[1] = b1;
    r[1] = 0, s[1] = 0;
    REPE(i, 2, n) {
        x[i] = (c * x[i - 1] + d * y[i - 1] + e1) % f;
        y[i] = (d * x[i - 1] + c * y[i - 1] + e2) % f;
    }
    REPE(i, 2, n) {
        r[i] = (c * r[i - 1] + d * s[i - 1] + e1) % 2;
        s[i] = (d * r[i - 1] + c * s[i - 1] + e2) % 2;
    }
    REPE(i, 1, n) {
        a[i] = r[i] == 0 ? x[i] : -x[i];
        b[i] = s[i] == 0 ? y[i] : -y[i];
    }
    vector<LL> aa, bb;
    aa = gen(a);
    bb = gen(b);
    /*
    REPE(i, 1, n) {
      LL sa = 0, sb = 0;
      REPE(j, i, n) {
        sa += a[j];
        sb += b[j];
        aa.PB(sa);
        bb.PB(sb);
      }
    }
    sort(ALL(aa));
    sort(ALL(bb));
    for (auto x : aa) cout << x << ' '; cout << endl;
    for (auto x : bb) cout << x << ' '; cout << endl;
    */
    using T = tuple<LL, int, int>;
    priority_queue<T> q;
    REP(i, SZ(aa)) {
        if (aa[i] <= 0)
            q.push({aa[i] * bb[0], i, 0});
        else
            q.push({aa[i] * bb[SZ(bb) - 1], i, SZ(bb) - 1});
    }
    while (k--) {
        LL s;
        int i, j;
        tie(s, i, j) = q.top();
        q.pop();
        if (k == 0) {
            fprintf(stderr, "cal %lld\n", s);
            printf("%lld\n", s);
            break;
        }
        if (aa[i] <= 0)
            j++;
        else
            j--;
        if (j >= 0 && j < SZ(bb)) q.push({aa[i] * bb[j], i, j});
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        solve();
    }
    return 0;
}
