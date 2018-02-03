// poj2356_Find_a_Multiple_math.cpp

// 鸽笼原理：n 个物品放在 m 个箱子里，至少有一个箱子物品多于 m / n 个
// 于是，本题中 accumulate[n] % N 共 N 个结果但只有 N - 1 个取值，至少有一个取值会重复。
// 而当 accumulate[n1] % N = accumulate[n2] % N, 必有
// sum(from n1+1 to n2+1) % N == 0

#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    int N; scanf("%d", &N);
    int num[N], mod_from[N], num_accumulate = 0;
    fill(mod_from, mod_from+N, 0);
    for(int i=0;i<N;i++){
        scanf("%d", num+i);
    }
    for(int i=0;i<N;i++){
        num_accumulate = num_accumulate + num[i];
        int mod = num_accumulate % N;
        if(mod == 0 || mod_from[mod] != 0){
            printf("%d\n", i-mod_from[mod]+1);
            for(int j=mod_from[mod];j<=i;j++){
                printf("%d\n", num[j]);
            }
            break;
        }
        else mod_from[mod] = i + 1;
    }
}
