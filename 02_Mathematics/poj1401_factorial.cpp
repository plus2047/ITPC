// poj1401_factorial.cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    int t; scanf("%d", &t);
    while(t--){
        int n; scanf("%d", &n);
        int n2 = 0, n5 = 0, f2 = 2, f5 = 5;
        while(f2 <= n){
            n2 += n / f2;
            f2 *= 2;
        }
        while(f5 <= n){
            n5 += n / f5;
            f5 *= 5;
        }
        printf("%d\n", min(n2, n5));
    }
}
