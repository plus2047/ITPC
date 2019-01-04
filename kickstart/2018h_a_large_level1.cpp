// for programing contest
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <random>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <map>
#include <stdexcept>

using namespace std;

typedef long long int lld;
typedef long long unsigned llu;

struct Node{
    Node* left;
    Node* right;
    bool is_leaf;
};

void insert(string& str, lld str_i, Node* root){
    if(root->is_leaf){
        return;
    }
    else if(str_i == str.size()){
        root -> is_leaf = true;
    }
    else if(str[str_i] == 'B'){
        if(root -> left == nullptr){
            root -> left = new Node{nullptr, nullptr, false};
        }
        insert(str, str_i + 1, root -> left);
    }
    else{
        if(root -> right == nullptr){
            root -> right = new Node{nullptr, nullptr, false};
        }
        insert(str, str_i + 1, root -> right);
    }
}

lld N, P, forbid_count = 0, ONE = 1;
void stat(Node* root, lld level){
    if(root == nullptr){
        return;
    }
    else if(root -> is_leaf){
        forbid_count += ONE << (N - level);
    }
    else{
        stat(root -> left, level + 1);
        stat(root -> right, level + 1);
    }
}

int main() {
    #ifdef __APPLE__
    freopen("_in_large.txt", "r", stdin);
    freopen("_out_cpp.txt", "w", stdout);
    #endif

    llu T; scanf("%llu", &T);
    for(llu t = 1; t <= T; t ++){
        scanf("%llu%llu", &N, &P);
        string _in;
        Node* root = new Node{nullptr, nullptr, false};
        for(llu i = 0; i < P; i++){
            cin >> _in;
            insert(_in, 0, root);
        }
        forbid_count = 0;
        stat(root, 0);
        printf("Case #%lld: %llu\n", t, (ONE << N) - forbid_count);
    }
}
