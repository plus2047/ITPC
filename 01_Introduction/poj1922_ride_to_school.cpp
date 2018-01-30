// poj1922_ride_to_school
// http://poj.org/problem?id=1922
#include <cstdio>
#include <cmath>
#include <climits>
using namespace std;

int main(){
    int min_arrive_at, speed, launch, n;
    while(scanf("%d", &n), n!=0){
        min_arrive_at = INT_MAX;
        for(int i=0;i<n;i++) {
            scanf("%d%d", &speed, &launch);
            if (launch < 0) continue;
            int arrive_at = 16200 / speed + launch;
            if (16200 % speed) arrive_at ++;
            if (arrive_at < min_arrive_at) min_arrive_at = arrive_at;
        }
        printf("%d\n", min_arrive_at);
    }
}
