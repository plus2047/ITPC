#include <cstdio>

int main() {
    double len = 0;
    while(scanf("%lf", &len)){
        if(len == 0) break;
        double sum = 0, i = 2;
        while(sum < len){
            sum += 1 / i;
            i += 1;
        }
        printf("%d card(s)\n", int(i) - 2);
    }
}
