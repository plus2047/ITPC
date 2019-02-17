// ===== programing contest template =========
// ===== using standrod: C++ 14 ==============
// ===== include all posible stl headers =====
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// ===== if using persional toolbox =====
// #define __TOOLBOX__
// ===== include persional toolbox ======
#ifdef __TOOLBOX__
#include "lib/graph.h"
#include "lib/hash.h"
#include "lib/show.h"
#include "lib/string.h"
using namespace contest;
#endif  // __TOOLBOX__
// for contest, it's okey to use namespace. =====
using namespace std;

// =============================================
// ============= CONTEST ENV BEGIN =============
typedef long long int LL;
typedef long long unsigned LLU;
#define G(_tuple, num) (get<num>(_tuple))
#define FOR(i, N) for (int i = 0, i##_len = (int)(N); i < i##_len; i++)
#define IFOR(i, N) for (int i = (int)(N)-1; i >= 0; i--)

// =============================================
// =============== CONTEST BEGIN ===============

// algorithm in official solution.
// my implement is too slow for large dataset.
// maybe because of attacking-data: words with
// same length & front & back.

int T, L, N;
LL A, B, C, D;
const int L_MAX = 2E4 + 8, N_MAX = 1E6 + 8;
const int N_CHAR = 26;
const int N_FB = N_CHAR * N_CHAR + 8;

vector<string> words(L_MAX);
vector<unordered_set<int>> fb2idx(N_FB);
#define ID(f, b) (((f) - 'a') * N_CHAR + (b) - 'a')
unordered_map<int, vector<int>> len2idx;
vector<vector<int>> char_count(L_MAX, vector<int>(26, 0));
vector<int> _count(26, 0);

char str[N_MAX];
vector<LL> x(N_MAX);

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d", &L);
        FOR(i, N_FB) fb2idx[i].clear();
        len2idx.clear();
        FOR(i, L) {
            cin >> words[i];

            int id = ID(words[i].front(), words[i].back());
            fb2idx[id].insert(i);

            len2idx[(int)words[i].size()].push_back(i);

            fill(char_count[i].begin(), char_count[i].end(), 0);
            for (char c : words[i]) char_count[i][c - 'a']++;
        }

        scanf("%s%s", str, str + 1);
        scanf("%d%lld%lld%lld%lld", &N, &A, &B, &C, &D);
        x[0] = str[0];
        x[1] = str[1];
        for (int i = 2; i < N; i++) {
            x[i] = (A * x[i - 1] + B * x[i - 2] + C) % D;
            str[i] = x[i] % N_CHAR + 'a';
        }
        str[N] = 0;

        int res = 0;
        vector<int> rm;
        for (auto& p : len2idx) {
            int word_len = p.first;
            fill(_count.begin(), _count.end(), 0);
            for (int right = 0; right < N; right++) {
                _count[str[right] - 'a']++;
                if (right >= word_len) {
                    _count[str[right - word_len] - 'a']--;
                }
                if (right >= word_len - 1) {
                    int id = ID(str[right - word_len + 1], str[right]);
                    rm.clear();
                    for (int word_idx : p.second) {
                        if (fb2idx[id].find(word_idx) != fb2idx[id].end() and
                            _count == char_count[word_idx]) {
                            res++;
                            rm.push_back(word_idx);
                        }
                    }
                    for (int i : rm) fb2idx[id].erase(i);
                }
            }
        }
        printf("Case #%d: %d\n", t, res);
        fprintf(stderr, "Case #%d: %d\n", t, res);
    }
}
