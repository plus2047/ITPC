// poj1785_Binary_Search_Heap_Construction.cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>

#define LABEL_LEN (100)
#define NODE_NUM (100)

struct TreapNode{
    char label[LABEL_LEN];
    int num;
};
TreapNode treapNode[NODE_NUM];
int nodeJumpMap[NODE_NUM];
bool comp_num(const int& index1, const int& index2){
    return treapNode[nodeJumpMap[index1]].num < treapNode[nodeJumpMap[index2]].num;
}
bool comp_label(const int& index1, const int& index2){
    return strcmp(treapNode[nodeJumpMap[index1]].label, treapNode[nodeJumpMap[index2]].label) < 0;
}
inline char* get_label(int index){return treapNode[nodeJumpMap[index]].label;}
inline int get_num(int index){return treapNode[nodeJumpMap[index]].num;}

int main(){
    if(!freopen("in.txt", "r", stdin)){ printf("fail."); return 0; }
    if(!freopen("out.txt", "w", stdout)){ printf("fail."); return 0; }
    int node_num;
    while(scanf("%d", &node_num), node_num!=0) {
        if (node_num == 0) return 0;
        for (int i = 0; i < node_num; i++) {
            nodeJumpMap[i] = i;
            scanf(" %[^/]/%d", treapNode[i].label, &treapNode[i].num);
        }
//        std::sort(nodeJumpMap, nodeJumpMap+node_num, comp_label);
    }
}
