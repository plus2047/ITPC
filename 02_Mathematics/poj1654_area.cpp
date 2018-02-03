// poj1654_area.cpp
#include <cstdio>
using namespace std;


char buff[1000000 + 100];
int delta[10][2] = {
        {0, 0}, // 0
        {-1, -1}, // 1
        {0, -1}, // 2
        {1, -1}, // 3
        {-1, 0}, // 4
        {0, 0}, // 5
        {1, 0}, // 6
        {-1, 1}, // 7
        {0, 1}, // 8
        {1, 1} // 9
};

int main(){
    int T; scanf("%d", &T);
    for(int t=0;t<T;t++){
        scanf("%s", buff);
        long long x = 0, y = 0;
        long long s2 = 0;
        for(char* i=buff;*i!='5';i++){
            long long nx = x + delta[*i-'0'][0], ny = y + delta[*i-'0'][1];
            s2 += x * ny - y * nx;
            x = nx; y = ny;
        }
        if(s2 < 0) s2 *= -1;
        printf("%lld", s2 / 2);
        if(s2 % 2) printf(".5\n");
        else printf("\n");
    }
}
