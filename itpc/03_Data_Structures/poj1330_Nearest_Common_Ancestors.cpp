// poj1330_Nearest_Common_Ancestors.cpp

#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
    int T; scanf("%d", &T);
    while(T--){
        int N; scanf("%d", &N);
        int jump[N+1];
        fill(jump, jump+N+1, 0);
        for(int i=1;i<N;i++){
            int father, son; scanf("%d%d", &father, &son);
            jump[son] = father;
        }
        int n1, n2; scanf("%d%d", &n1, &n2);
        int path1[N+1], path2[N+1], end1=0, end2=0;
        path1[end1] = n1; path2[end2] = n2;
        while(path1[end1] != 0){
            end1 ++;
            path1[end1] = jump[path1[end1-1]];
        }
        while(path2[end2] != 0){
            end2 ++;
            path2[end2] = jump[path2[end2-1]];
        }
        while(path1[end1] == path2[end2]){
            end1--;
            end2--;
        }
        printf("%d\n", path1[end1+1]);
    }
}
