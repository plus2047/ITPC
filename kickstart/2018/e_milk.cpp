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

template <int group = 16, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
#endif
}

// ===== personal contest template =====

// ========== contest code ==========

void solve(int _turn) {
    int N, M, P;
    scanf("%d%d%d", &N, &M, &P);

    vector<string> req(N), forbid(M);
    rep(i, N) { cin >> req[i]; }
    rep(i, M) { cin >> forbid[i]; }

    vector<int> weight(P);
    rep(i, N) rep(j, P) {
        if (req[i][j] == '1') weight[j]++;
    }
    // show("weight: ", allof(weight));

    vector<pair<int, string>> best = {{0, ""}}, _best;
    rep(i, P) {
        _best.clear();
        for (auto& p : best) {
            for (int append = 0; append <= 1; append++) {
                _best.push_back(p);
                _best.back().second.push_back('0' + append);
                _best.back().first += append == 0 ? weight[i] : N - weight[i];
            }
        }
        if (_best.size() > M + 1) {
            sort(allof(_best));
            _best.resize(M + 1);
        }
        swap(best, _best);
    }

    sort(allof(forbid));
    int res = -1;
    for (const auto& p : best) {
        if (!binary_search(allof(forbid), p.second)) {
            res = p.first;
            break;
        }
    }
    printf("Case #%d: %d\n", _turn, res);
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in building command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
