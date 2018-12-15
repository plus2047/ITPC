// poj2693_Chocolate_Chip_Cookies.cpp
// !!! CANNOT AC. Wrong Answer. WITHDRAW.

#include <cmath>
#include <cstdio>
using namespace std;

const double R2 = 6.25, D2 = 25., DELTA = 0.0000000001, R2P = R2 + DELTA;
const int P_N = 200;

double px[P_N], py[P_N], c1x, c1y, c2x, c2y;

double d2(double p1x, double p1y, double p2x, double p2y) {
    double dx = p1x - p2x, dy = p1y - p2y;
    return dx * dx + dy * dy;
}

void get_c(int i, int j) {
    double mx = (px[i] + px[j]) / 2, my = (py[i] + py[j]) / 2;
    double dx1 = px[i] - mx, dy1 = py[i] - my;
    double d12 = dx1 * dx1 + dy1 * dy1, d1 = sqrt(d12), d2 = sqrt(R2 - d12);
    double k = d2 / d1, dx2 = dy1 * k, dy2 = dx1 * k;
    c1x = mx + dx2;
    c1y = my - dy2;
    c2x = mx - dx2;
    c1y = my + dy2;
}

int main() {
#ifdef __APPLE__
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int n = 0;
    while (scanf("%lf%lf", px + n, py + n) == 2) n++;
    if (n == 1) {
        printf("1\n");
        return 0;
    }

    int max_r = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (d2(px[i], py[i], px[j], py[j]) > D2) continue;
            get_c(i, j);
            int n1 = 0, n2 = 0;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) {
                    n1++;
                    n2++;
                } else {
                    if (d2(px[k], py[k], c1x, c1y) < R2P) n1++;
                    if (d2(px[k], py[k], c2x, c2y) < R2P) n2++;
                }
            }
            if (max_r < n1) max_r = n1;
            if (max_r < n2) max_r = n2;
        }
    }
    printf("%d\n", max_r);
}
