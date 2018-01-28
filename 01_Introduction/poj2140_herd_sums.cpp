#include <cstdio>
using namespace std;

int main(){
    int N; scanf("%d", &N);
    int count =0;
    int left=0, right=1, sum=1;
    while(right<=N){
        if(sum==N){
            count ++;
            right ++;
            sum += right;
        }
        else if(sum < N){
            right ++;
            sum += right;
        }
        else{
            sum -= left;
            left ++;
        }
    }
    printf("%d\n", count);
}
