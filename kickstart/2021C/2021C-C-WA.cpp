// ===== programing contest template ======

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

typedef long long int lld;
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

// #undef __LOCAL__

template <typename ITER>
void print(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void print(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ========== contest code ==========
inline double getRockScore(int rock, int paper, int scissor, int W, int E) {
    double total = rock + paper + scissor;
    return rock / total * E + scissor / total * W;
}

void solve(int _turn) {
    int W, E;
    scanf("%d%d", &W, &E);

    const int ND = 60;
    static double score[ND + 1][ND + 1][ND + 1];  // [rock, paper, scissor]
    static char act[ND + 1][ND + 1][ND + 1];      // [rock, paper, scissor]
    memset(score, 0, sizeof(score));
    memset(act, 0, sizeof(act));

    int rock = -1, paper = -1, scissor = -1;
    double maxScore = 0;
    for (int i = 0; i <= ND; i++) {
        for (int j = 0; i + j <= ND; j++) {
            for (int k = 0; i + j + k <= ND; k++) {
                double currScore = 0;
                char currAct = 0;
                if (i + j + k == 0) {
                    // nothing to do
                } else if (i + j + k == 1) {
                    currScore = (W + E) / 3.0;
                    currAct = 'R';
                } else {
                    if (i) {
                        double s = getRockScore(i - 1, j, k, W, E) +
                                   score[i - 1][j][k];
                        if(s > currScore) {
                            currScore = s;
                            currAct = 'R';
                        }
                    }
                    if (j) {
                        double s = getRockScore(j - 1, k, i, W, E) +
                                   score[i][j - 1][k];
                        if(s > currScore) {
                            currScore = s;
                            currAct = 'P';
                        }
                    }
                    if (k) {
                        double s = getRockScore(k - 1, i, j, W, E) +
                                   score[i][j][k - 1];
                        if(s > currScore) {
                            currScore = s;
                            currAct = 'S';
                        }
                    }
                }
                score[i][j][k] = currScore;
                act[i][j][k] = currAct;
                if(i + j + k == ND and currScore > maxScore) {
                    rock = i, paper = j, scissor = k;
                    maxScore = currScore;
                }
            }
        }
    }
    char res[ND + 1] = {};
    for(int x = ND; x > 0; x--) {
        res[x - 1] = act[rock][paper][scissor];
        if(res[x - 1] == 'R') {
            rock--;
        } else if(res[x - 1] == 'P') {
            paper--;
        } else {
            scissor--;
        }
    }
    // print("max score: %lf\n", maxScore);
    printf("Case #%d: %s\n", _turn + 1, res);
}

int main() {
    int T, X;
    scanf("%d%d", &T, &X);
    rep(t, T) { solve(t); }
}
