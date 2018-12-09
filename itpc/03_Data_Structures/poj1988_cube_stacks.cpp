// poj1988_cube_stacks.cpp
#include <algorithm>
#include <cstdio>

#define MAX_N (30000)

struct Cube{
    int father, distance;
};

Cube cube[MAX_N+1];
char buff[100];

inline int get_father(int x){return cube[x].father;}
inline int get_root(int x){
    int f = get_father(x), gf = get_father(f);
    if(gf == f) return f;
    else{
        int root = get_root(f);
        cube[x].father = root;
        cube[x].distance += cube[f].distance;
        return root;
    }
}

void _move(int x, int y){
    int rootx = get_root(x), rooty = get_root(y);
    int dx = cube[rootx].distance, dy = cube[rooty].distance;
    cube[rootx].father = rooty;
    cube[rooty].distance += dx;
    cube[rootx].distance = dy;
}

int _count(int x){
    int root = get_root(x);
    if(root == x) return 0;
    else return cube[x].distance;
}

int main(){
//    if(!freopen("in.txt", "r", stdin)){ printf("fail."); return 0; }
//    if(!freopen("out.txt", "w", stdout)){ printf("fail."); return 0; }
    for(int i=1;i<=MAX_N;i++){cube[i].father = i; cube[i].distance=1;}
    int p; scanf("%d", &p);
    for(int i=0;i<p;i++){
        scanf("%s", buff);
        if(buff[0] == 'M'){
            int x, y; scanf("%d%d", &x, &y);
            _move(x, y);
        }
        else{
            int x; scanf("%d", &x);
            printf("%d\n", _count(x));
        }
//        for(int j=1;j<=6;j++){
//            printf("cube: %d, father: %d, distance: %d.\n", j, cube[j].father, cube[j].distance);
//        }
//        printf("\n");
    }
}
