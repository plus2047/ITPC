# 二叉树

在算法竞赛中，各类二叉树是唯一可以现场实现的复杂数据结构。本文总结二叉树和二叉树的各类变体，以及这些变体的应用和简易实现。

[TOC]

## 二叉树基础

一份简明的二叉树实现。

```cpp
typedef int Val;
struct TNode{
    TNode *left = NULL, *right = NULL;
    Val val = 0;
    TNode(Val _val): val(_val) {}
};
TNode* insert(TNode* root, Val val){
    while(true){
        if(root->val == val) return NULL;
        TNode **p_next = &(root->val > val ? root->left : root->right);
        if(*p_next == NULL) return *p_next = new TNode(val);
        else root = *p_next;
    }
}
```

这里没有实现删除算法。删除节点时，只要使用右子树最左节点（或左子树最右节点）进行替代即可，然后用于替代的节点本身留下的空位递归使用删除算法。另外**一种算法竞赛中取巧的删除算法是使用「墓碑」，标记删除但不真正删除**。

二叉树的基本调整技巧为旋转，具体分为节点和其父节点两个节点的旋转，或者节点、父节点、祖父节点三个节点的旋转。这些旋转技巧看似复杂，实际上就是把要旋转的节点从二叉树上断开，然后这两个或三个节点从一种可能的组合调整到另一种可能的组合（两个节点有两种合法的组合，三个节点至少有 5 种合法的组合），然后把被旋转节点的子树挂回到正确的位置（旋转不改变子树个树）。

## 自平衡二叉树：伸展树 Splay Tree & 红黑树 Red-Black Tree

伸展树的规则比较简单：被访问的节点总是会被调整到根结点。调整方式是，只要该节点有祖父节点，就使用三节点调整技巧将其调整到根结点。没有祖父节点（此时其父节点就是根结点）则使用双节点调整技巧。

伸展树的均摊时间复杂度并不弱于其他平衡二叉树，但没有最坏时间复杂度的保证。

另一种平衡二叉树是 AVL 树，但因为其「平衡性」太好导致进行修改时调整成本较高，总体性能低于红黑树。

红黑树是最广泛使用的平衡二叉树该树在调整复杂度和平衡程度上取得一定的折中。红黑树只对每个节点附加一个颜色标记，红色节点或者黑色节点。然后红黑树满足以下条件：

1. 节点是红色或黑色。
2. 根是黑色。
3. 所有叶子都是黑色（叶子是虚节点 NULL）。
4. 每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
5. 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。

最后两条性质保证了红黑树「不至于太严重的失衡」。

红黑树的插入操作遵从以下思路（该思路在竞赛现场实现很困难，但在纸面上推演的问题不大）：先按照一般二叉树的插入技巧插入节点，并将该节点着色为红色。如果没有发生双红冲突，则插入成功。发生冲突按照以下规则进行调整，调整的重点是解决双红冲突或者将双红冲突向上递归传递，同时保证每条路径上黑色节点个数不变。
如果发生双红冲突，则其祖父节点一定是黑色节点。此时如果叔父节点也是红色节点，则将父节点和叔父节点着色为黑色并将祖父节点着色为红色，并关于祖父节点递归向上调整冲突。如果叔父节点为黑色，则关于父节点、祖父节点进行三节点调整，可以简单的验证，将这三个节点调整为一个父节点两个字节点的形式之后，一定有办法进行着色，保证既没有双红冲突（限于新的父节点对应的子树中），也没有改变每条路径的黑节点个数。这样的调整会将红色节点调整到根结点，然后继续递归解决冲突。
调整过程最终可能会将红色节点调整到根结点，此时直接将根节点颜色变更为黑色节点即可。

红黑树的删除比插入还要复杂（该思路复杂到在纸面上推演都很困难）。删除算法首先假设要删除的节点只有一个儿子（否则将该节点与其直接后继对调之后再删除即可）。删除该节点之后，将其儿子节点像链表一样移动到该节点，并将该节点的颜色「追加」到移动到该位置的儿子节点上。于是现在新节点是两种颜色的叠加（这主要是为了维护每条路径上黑色节点数目相等，因此不能随便删除黑色节点）。新节点如果不是黑加黑，就只能是红加黑，直接算做黑色即可。问题主要是该节点是黑加黑的情况下如何调整。
调整思路首先是想办法把一重黑色递归的转移到父节点上，这就要求其兄弟节点也要转移一重黑色到父节点上。如果兄弟节点是红色节点，则父节点是黑色节点，将兄弟节点与父节点先对调再继续。之后根据兄弟节点的子节点（外甥节点）颜色进行调整。如果两个外甥节点都是黑色，直接将兄弟节点的黑色转移到父节点上，然后向上递归。
外甥节点有红色节点的情况，冲突附近的红色节点足够多，其主要思路是借助旋转把一个红色节点转移到黑加黑节点的前方，然后把黑加黑节点的一重黑色转移上去，结束调整。如果左外甥节点为红色右外甥节点为黑色，以兄弟节点为支点右旋并调整颜色，可以转换为下一种情况。如果右外甥节点为红色左外甥节点颜色任意，则以根结点为支点左旋并调整颜色，可以结束调整。

## Treap 树堆 & Cartesian Tree 笛卡尔树

由于使用 STL 的红黑树可以组合以任意个键值高速有序检索的数据结构，树堆如果仅仅是作为树和堆的组合则意义不大，但是这里仍然整理一下。

树堆是同时根据两个键值建立的数据结构，根据树键值，树堆是一棵二叉搜索树。根据堆键值，树堆是一个堆。树堆的堆键值如果使用随机数，那可以将树堆视为一种自平衡二叉树。或者特定应用场景中堆键值有特殊的意义。

树堆的插入和删除都比较简单。插入时，首先按照一般的二叉搜索树插入步骤进行删除。如果插入的节点大于根结点，直接对插入节点和根结点进行旋转并递归处理即可（其调整步骤比 Splay 树还要简单）。删除时按照一般的二叉树删除步骤进行删除，但是如果节点有两个子节点，则用于替换的后继节点的堆键值可能破坏堆性质，需要进行向上或者向下调整。

[笛卡尔树](https://en.wikipedia.org/wiki/Cartesian_tree)是一种特殊的 Treap. 笛卡尔树跟一个数组关联，其树键值为数组下标，堆键值为数组中存储的数值。不难发现，笛卡尔树也能够处理范围最值查询问题（然而 Segment Tree 也能处理范围最值问题）。

笛卡尔树有快速建树算法，因此也视为一种在数组上快速建树堆的算法。其基本思路是，现将节点按照树键值排序，然后插入时就一定是沿着最右子节点链插入，建树时间复杂度 O(N), 排序时间复杂度 O(N log N). 这里有一份值得参考的代码：

```cpp
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

        node[0].num = INT_MAX;
        node[0].r_child = index_array[1];
        node[0].l_child = NO_CHILD;
        node[0].label[0] = 0;  // fake root
        
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
```

## Segment Tree / Interval Tree / Fenwick Tree

注意，以下几种数据结构名称比较混乱，只保证本工程内部自洽。

[Fenwick Tree](https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/) 是一个满树，有非常优雅的实现。其另一个优势是能够被扩展到任意纬度。

[Segment Tree](https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/) 是一个比较易懂的平衡二叉树。除了求和问题之外，Segment Tree 能够方便的修改用于求区间极值问题。用于这些问题时，Segment Tree 一般也会实现为满树，

[Interval Tree](https://www.geeksforgeeks.org/interval-tree/) 是关于一系列给定的区间建树，然后用于查询目标区间与树中存储的哪些区间重叠等。

仔细考虑后发现这两种树看似有很大的不同，实际上可以总结为以下特征：按照区间的某个特性（如左端点）作为键值建树，然后在节点上保存子树的最大值、最小值、和等信息。如果区间不是规整的区间，还可以在节点上保存子树的区间覆盖范围信息。进行查询时，能够根据左右节点覆盖范围进行递归。为了便于编程，对于静态查询问题，可以把区间全都储存在叶节点上，建立满树。非叶节点只保存子树「统计信息」。对于动态问题（有增删操作），则只能手写二叉树。由于节点上需要保存子节点的统计信息，不能使用 STL SET 实现。

## 总结

这些树相关数据结构可以分为几大类：

- 自平衡二叉树。除了 AVL / 红黑树 / Splay 树，Treap 也可以被用作自平衡二叉树。
- Treap. 其双键值特性既可以被用到平衡算法中（可能是最容易实现的平衡二叉树，同时不像 Splay 树容易构造对抗样本）也可以赋予堆键值特殊意义用于处理特定问题。注意，Treap 的两个键值确定之后，树的结构是唯一的。
- Segment Tree. 区间查询相关问题，包括区间覆盖、区间极值、区间和等。关于区间左端点或右端点建树，在节点上维护关于整个子树的区间特征。
- 一些优秀实现，如笛卡尔树的建树算法，Fenwick 树。
