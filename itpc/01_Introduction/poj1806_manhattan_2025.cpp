#include <algorithm>
#include <cstdio>
using namespace std;

int map[19][19][19];
int n = 0;
int d[6][3] = {{0, 0, 1},  {0, 0, -1}, {0, 1, 0},
               {0, -1, 0}, {1, 0, 0},  {-1, 0, 0}};

void fill_near(int i, int j, int k) {
    if (map[i][j][k] >= n) return;
    int next_d = map[i][j][k] + 1;
    for (int a = 0; a < 6; a++) {
        if (map[i + d[a][0]][j + d[a][1]][k + d[a][2]] > next_d) {
            map[i + d[a][0]][j + d[a][1]][k + d[a][2]] = next_d;
            fill_near(i + d[a][0], j + d[a][1], k + d[a][2]);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d", &n);
        fill((int*)map, (int*)(map) + 19 * 19 * 19, n + 1);
        map[9][9][9] = 0;
        fill_near(9, 9, 9);

        printf("Scenario #%d:\n", t);
        for (int i = -n; i <= n; i++) {
            printf("slice #%d:\n", i + n + 1);
            for (int j = -n; j <= n; j++) {
                for (int k = -n; k <= n; k++) {
                    if (map[9 + i][9 + j][9 + k] == n + 1)
                        printf(".");
                    else
                        printf("%d", map[9 + i][9 + j][9 + k]);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
}
