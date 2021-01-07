#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool row[9][10], col[9][10], blk[9][10];
int target[128], cnt[128];
char grid[9][16], res[9][16];
vector<tuple<int, int, int> > ps;  // <cnt, i, j>

bool dfs(int pidx) {
    if (pidx == int(ps.size())) return true;
    int i = get<1>(ps[pidx]), j = get<2>(ps[pidx]);
    int bidx = i / 3 * 3 + j / 3, c = grid[i][j];
    for (int k = 1; k <= 9; k++) {
        if (not row[i][k] and not col[j][k] and not blk[bidx][k]) {
            target[c] -= k;
            cnt[c]--;
            row[i][k] = col[j][k] = blk[bidx][k] = true;
            if (target[c] >= cnt[c] and target[c] <= cnt[c] * 9) {
                if (dfs(pidx + 1)) {
                    res[i][j] = '0' + k;
                    return true;
                }
            }
            target[c] += k;
            cnt[c]++;
            row[i][k] = col[j][k] = blk[bidx][k] = false;
        }
    }
    return false;
}

int main() {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(blk, 0, sizeof(blk));
    memset(target, 0, sizeof(target));
    memset(cnt, 0, sizeof(cnt));
    memset(res, 0, sizeof(res));
    ps.clear();

    for (int i = 0; i < 9; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < 9; j++) {
            cnt[grid[i][j]]++;
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ps.push_back({cnt[grid[i][j]], i, j});
        }
    }
    sort(ps.begin(), ps.end());

    char buff[16];
    int total;
    while (scanf("%s%d", buff, &total) != EOF) {
        target[buff[0]] = total;
    }

    bool succ = dfs(0);
    if (succ) {
        for (int i = 0; i < 9; i++) {
            printf("%s\n", res[i]);
        }
    } else {
        printf("FAIL\n");
    }
}
