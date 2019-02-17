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

// using hash-like skill.

int T, L, N;
LL A, B, C, D;
const int L_MAX = 2E4 + 8, N_MAX = 1E6 + 8;
const int N_CHAR = 26;
const int N_FB = N_CHAR * N_CHAR + 8, L_TOTAL_MAX = 1E5 + 8;

unordered_set<int> word_lens;
typedef vector<int16_t> Word;
map<Word, int> dict;
Word word(N_CHAR + 2);

char buff[L_TOTAL_MAX], str[N_MAX];
int x[N_MAX];

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d", &L);
        word_lens.clear();
        dict.clear();
        FOR(i, L) {
            scanf("%s", buff);
            int word_l = strlen(buff);
            word_lens.insert(word_l);
            fill(word.begin(), word.end(), 0);
            word[N_CHAR] = buff[0];
            word[N_CHAR + 1] = buff[word_l - 1];
            FOR(i, word_l) word[buff[i] - 'a']++;
            dict[word]++;
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
        for (int len : word_lens) {
            fill(word.begin(), word.end(), 0);
            for (int right = 0; right < N; right++) {
                word[str[right] - 'a']++;
                if (right >= len) {
                    word[str[right - len] - 'a']--;
                }
                if (right >= len - 1) {
                    word[N_CHAR] = str[right - len + 1];
                    word[N_CHAR + 1] = str[right];
                    auto f = dict.find(word);
                    if (f != dict.end()) {
                        res += f->second;
                        dict.erase(f);
                    }
                }
            }
        }
        printf("Case #%d: %d\n", t, res);
        fprintf(stderr, "Case #%d: %d\n", t, res);
    }
}
