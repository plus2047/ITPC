// poj2085_Inversion.cpp

#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m), n >= 1 && m >= 0){
        int r = (int)ceil( (1 + sqrt(1+8.0*m)) / 2),
                a = (int)(n - ((long long int)(r) * (r - 1) / 2 - m));
        for(int i=1;i<=(n-r);i++){
            printf("%d ", i);
        }
        printf("%d ", a);
        for(int i=n;i>(n-r);i--){
            if(i==a) continue;
            printf("%d ", i);
        }
        printf("\n");
    }
}
