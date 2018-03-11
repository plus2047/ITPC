// poj1984_Navigation_Nightmare_WA.cpp
// !!!WA
// Anti-block: review this code at 180211
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_N (40010)
#define MAX_M (40010)
#define MAX_K (10010)
#define BUFF_SIZE (100)

int M, N, K, L;
char buff[BUFF_SIZE];

struct Edge{ int f1, f2, rx, ry; };
struct Enquiry{ int f1, f2, I, index, ans; };
struct Farm{ int rx, ry, father; };

Edge edge[MAX_M];
Farm farm[MAX_N];
Enquiry enquiry[MAX_K];

bool compare_enquiry_I(const Enquiry &e1, const Enquiry &e2){ return e1.I < e2.I; }
bool compare_enquiry_index(const Enquiry &e1, const Enquiry &e2){ return e1.index < e2.index; }

int root(int index){
    int f = farm[index].father;
    if(farm[f].father == f){
        return f;
    }
    else{
        int r = root(f);
        farm[index].rx += farm[f].rx;
        farm[index].ry += farm[f].ry;
        farm[index].father = r;
        return r;
    }
}

void do_enquiry(int index){
    int f1 = enquiry[index].f1, f2 = enquiry[index].f2;
    if(root(f1) != root(f2)) enquiry[index].ans = -1;
    else enquiry[index].ans = abs(farm[f1].rx-farm[f2].rx) + abs(farm[f1].ry-farm[f2].ry);
}

int main(){
    scanf("%d%d", &N, &M);
    for(int i=1;i<=M;i++){
        scanf("%d%d%d%s", &edge[i].f1, &edge[i].f2, &L, buff);
        switch(buff[0]){
            case 'E': edge[i].rx = L; edge[i].ry = 0; break;
            case 'W': edge[i].rx = -L; edge[i].ry = 0; break;
            case 'N': edge[i].rx = 0; edge[i].ry = L; break;
            case 'S': edge[i].rx = 0; edge[i].ry = -L; break;
            default: throw;
        }
    }
    scanf("%d", &K);
    for(int i=1;i<=K;i++){
        scanf("%d%d%d", &enquiry[i].f1, &enquiry[i].f2, &enquiry[i].I);
        enquiry[i].index = i;
    }
    sort(enquiry + 1, enquiry + K + 1, compare_enquiry_I);
    for(int i=1;i<=N;i++){ farm[i].rx = 0; farm[i].ry = 0; farm[i].father = i; }

    int enquiry_i = 1;
    for(Edge* e=edge+1;e!=edge+M+1;e++){
        int r1 = root(e->f1), r2 = root(e->f2);
        if(r1 != r2){
            farm[r1].father = r2;
            farm[r1].rx = e->rx + farm[e->f2].rx - farm[e->f1].rx;
            farm[r1].ry = e->ry + farm[e->f2].ry - farm[e->f1].ry;
        }
        else throw ;
        while(enquiry_i <= K && enquiry[enquiry_i].I <= (e - edge)){
            do_enquiry(enquiry_i);
            enquiry_i++;
        }
    }
    sort(enquiry + 1, enquiry + K + 1, compare_enquiry_index);
    for(int i=1;i<=K;i++) printf("%d\n", enquiry[i].ans);
}
