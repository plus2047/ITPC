// for programing contest
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAX_N (110)
char field[MAX_N][MAX_N];

int main() {
#ifdef __APPLE__
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
#define SQARE(x) ((x) * (x))
#define FIELD(x) ((x) >= 0 && (x) < N)

    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s\n", field[i]);
    }

    int max_area = 0;
    for (int x1 = 0; x1 < N; x1++) {
        for (int y1 = 0; y1 < N; y1++) {
            if (field[x1][y1] != 'J') continue;
            for (int x2 = x1; x2 < N; x2++) {
                for (int y2 = y1 + 1; y2 < N; y2++) {
                    if (field[x2][y2] != 'J') continue;

                    int area = SQARE(x1 - x2) + SQARE(y1 - y2);
                    if (area <= max_area) continue;

                    int dx = x1 - x2, dy = y1 - y2;
                    int x3, y3, x4, y4;

                    int sign = -1;
                    for(int _i = 0; _i < 2; _i ++){
                        sign *= -1;
                        x3 = x1 - sign * dy, y3 = y1 + sign * dx;
                        x4 = x2 - sign * dy, y4 = y2 + sign * dx;

                        if (FIELD(x3) && FIELD(x4) && FIELD(y3) && FIELD(y4) &&
                            field[x3][y3] != 'B' && field[x4][y4] != 'B') {
                            if(field[x3][y3] == 'J' || field[x4][y4] == 'J'){
                                max_area = area;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", max_area);
}
