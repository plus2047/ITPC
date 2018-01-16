#include <cstdio>

int main() {
    float input=0, sum=0;
    for(int i=0; i < 12; i++){
        scanf("%f", &input);
        sum += input;
    }
    printf("$%.2f\n", sum / 12);
    return 0;
}
