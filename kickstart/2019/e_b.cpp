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

void solve(int _turn) {
    int D, S;
    scanf("%d%d", &D, &S);

    typedef pair<LL, LL> Slot;
    vector<Slot> slots(S);  // <gain1, gain2>
    rep(i, S) { scanf("%lld%lld", &slots[i].first, &slots[i].second); }

    typedef tuple<LL, LL, int> Query;
    vector<Query> queries(D);  // <target1, target2, queryId>
    rep(i, D) {
        LL n1, n2;
        scanf("%lld%lld", &n1, &n2);
        queries[i] = {n1, n2, i};
    }

    sort(allof(slots), [](const Slot& a, const Slot& b) {
        return a.first * b.second > b.first * a.second;
    });

    LL totalGain1 = 0, totalGain2 = 0;
    for(const Slot& s: slots) {
        totalGain2 += s.second;
    }

    sort(allof(queries));

    string resStr(D, '?');
    int slotIdx = 0;
    for(const Query& q: queries) {
        LL target1, target2;
        int charIdx;
        tie(target1, target2, charIdx) = q;

        while(slotIdx < S and totalGain1 + slots[slotIdx].first <= target1) {
            totalGain1 += slots[slotIdx].first;
            totalGain2 -= slots[slotIdx].second;
            slotIdx++;
        }

        char res = 'Y';
        if(slotIdx == S) {
            res = target1 <= totalGain1 and target2 <= totalGain2 ? 'Y' : 'N';
        } else {
            LL needed1 = target1 - totalGain1, s1, s2;
            tie(s1, s2) = slots[slotIdx];
            res = target2 * s1 <= totalGain2 * s1 - needed1 * s2 ? 'Y' : 'N';
        }
        resStr[charIdx] = res;
    }

    printf("Case #%d: %s\n", _turn, resStr.c_str());
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
