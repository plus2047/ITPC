#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>

#include <array>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    int T, N;
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        scanf("%d", &N);
        int even_cnt = 0, odd_cnt = 0, even_num, odd_num[2];
        for(int n = 0; n < N; n++) {
            int num;
            scanf("%d", &num);
            if(num % 2) {
                odd_cnt++;
                odd_num[odd_cnt % 2] = n + 1;
            } else {
                even_cnt++;
                even_num = n + 1;
            }
        }
        if(even_cnt) {
            printf("1\n%d\n", even_num);
        } else if(odd_cnt >= 2){
            printf("2\n%d %d\n", odd_num[0], odd_num[1]);
        } else {
            printf("-1\n");
        }
    }
}
