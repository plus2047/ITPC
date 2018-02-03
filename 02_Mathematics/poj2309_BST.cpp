// poj2309_BST.cpp
#include <cstdio>
using namespace std;

int main(){
    int T; scanf("%d", &T);
    for(int t=0;t<T;t++){
        int x, depth = 0;
        scanf("%d", &x);
        while(x % (1 << depth) == 0) depth ++;
        int step = (1 << (depth - 1)) - 1;
        printf("%d %d\n", x - step, x + step);
    }
}
