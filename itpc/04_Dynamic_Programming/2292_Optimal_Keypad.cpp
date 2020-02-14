// ===== programing contest template ======
// ===== using a very very old C++ version =====

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

#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int lld;
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); ++i)

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
    fflush;
#endif  // __LOCAL__
}

// ===== personal contest template =====

// ========== contest code ==========

inline int get_id(char c) {
    if (isalpha(c)) return c - 'a';
    if (c == '+') return 26;
    if (c == '*') return 27;
    if (c == '/') return 28;
    if (c == '?') return 29;
    printf("unsupport char in input string.\n");
    fflush(stdout);
    exit(-1);
}
const char STR[] = "abcdefghijklmnopqrstuvwxyz+*/?";

int main() {
    const int C_NUM = 30, K_NUM = 12, STR_MAX_LEN = 32;
    int T, M;
    scanf("%d", &T);
    rep(t, T) {
        scanf("%d", &M);
        int count[C_NUM] = {0};
        char buff[STR_MAX_LEN];
        rep(i, M) {
            scanf("%s", buff);
            for (char* p = buff; *p != 0; ++p) {
                count[get_id(*p)]++;
            }
        }
        show("count: ", count, count + C_NUM);

        int cost[C_NUM][C_NUM];
        rep(i, C_NUM) {
            rep(j, C_NUM) {
                if (i > j) {
                    cost[i][j] = 0;
                } else if (i == j) {
                    cost[i][j] = count[i];
                } else {
                    cost[i][j] = cost[i][j - 1] + count[j] * (j - i + 1);
                }
                echo("%d ", cost[i][j]);
            }
            echo("\n");
        }

        int dp[C_NUM][K_NUM + 1];
        int next_begin[C_NUM][K_NUM + 1];
        for (int i = C_NUM - 1; i >= 0; i--) {
            for (int j = 1; j <= K_NUM; j++) {
                int &v = dp[i][j], &n = next_begin[i][j];
                if (j > C_NUM - i) {
                    v = INT_MAX;
                    n = -1;
                    continue;
                }
                if (j == 1) {
                    v = cost[i][C_NUM - 1];
                    n = -1;
                    continue;
                }
                v = INT_MAX;
                n = -1;
                for (int _i = i + 1; _i < C_NUM; _i++) {
                    if (dp[_i][j - 1] == INT_MAX) continue;
                    int _c = cost[i][_i - 1] + dp[_i][j - 1];
                    if (_c < v) {
                        v = _c;
                        n = _i;
                    }
                }
            }
        }
        echo("%d\n", dp[0][K_NUM]);

        for (int j = K_NUM, i = next_begin[0][K_NUM]; j > 1; j--) {
            buff[K_NUM - j] = STR[i];
            echo("%d %d\n", i, dp[i][j - 1]);
            i = next_begin[i][j - 1];
        }
        buff[K_NUM - 1] = 0;
        printf("%s\n", buff);
    }
}
