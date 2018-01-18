#include <cstdio>
using namespace std;

int reverse(int n){
    bool begin=false;
    int r=0;
    while(n){
        int last = n % 10;
        n /= 10;
        if(last || begin){
            r *= 10;
            r += last;
            begin = true;
        }
    }
    return r;
}

int main(){
    int N; scanf("%d", &N);
    while(N--){
        int a, b; scanf("%d%d", &a, &b);
        printf("%d\n", reverse(reverse(a) + reverse(b)));
    }
}
