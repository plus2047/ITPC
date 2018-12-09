// poj1799_gun.cpp
#include <cstdio>
#include <cmath>
using namespace std;

const double PI = 3.1415926535897932;

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        double circle_r; int bullet_n;
        scanf("%lf%d", &circle_r, &bullet_n);
        printf("Scenario #%d:\n", i);
        if(bullet_n <= 2) printf("%.3f\n\n", circle_r / bullet_n);
        else printf("%.3f\n\n", circle_r / (1 + 1 / sin(PI / bullet_n)));
    }
}
