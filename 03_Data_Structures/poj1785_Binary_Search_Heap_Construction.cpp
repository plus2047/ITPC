// poj1785_Binary_Search_Heap_Construction.cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

#define LABEL_LEN (100+5)
#define NODE_NUM (50000+5)
#define NO_CHILD (-1)

struct Node{
        char label[LABEL_LEN];
        int num, l_child, r_child, father;
};
Node node[NODE_NUM];
int index_array[NODE_NUM];

void dfs_print(int root_index){
    if(root_index == NO_CHILD) return;
    printf("(");
    dfs_print(node[root_index].l_child);
    printf("%s/%d", node[root_index].label, node[root_index].num);
    dfs_print(node[root_index].r_child);
    printf(")");
}

void insert(int index, int last_index){
    while(node[last_index].num < node[index].num) last_index = node[last_index].father;
    node[index].l_child = node[last_index].r_child;
    node[index].r_child = NO_CHILD;
    node[index].father = last_index;
    node[last_index].r_child = index;
}

bool comp_label(const int &index_1, const int &index_2){
    return strcmp(node[index_1].label, node[index_2].label) < 0;
}

int main(){
    int node_num;
    while(scanf("%d", &node_num) == 1 && node_num){
        for(int i=1;i<=node_num;i++){
            scanf(" %[a-z]/%d", node[i].label, &node[i].num);
            index_array[i] = i;
        }
        sort(index_array + 1, index_array + 1 + node_num, comp_label);

        // fake root
        node[0].num = INT_MAX;
        node[0].r_child = index_array[1];
        node[0].l_child = NO_CHILD;

        node[index_array[1]].father = 0;
        node[index_array[1]].l_child = NO_CHILD;
        node[index_array[1]].r_child = NO_CHILD;

        for(int i=2;i<=node_num;i++){
            insert(index_array[i], index_array[i-1]);
        }

        dfs_print(node[0].r_child);
        printf("\n");
    }
}
