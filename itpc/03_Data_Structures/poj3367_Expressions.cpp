// poj3367_Expressions.cpp
// do not call 'new' too much times.
// take care of IO time.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_STR_SIZE = 10000 + 10;

struct ExpTree{
    char c;
    ExpTree* left; ExpTree* right;
};

typedef vector<ExpTree*> VEP;
typedef vector<VEP> VVEP;

ExpTree node_list[MAX_STR_SIZE];
int new_node_index = 0;
ExpTree* new_node(char _c, ExpTree* _left, ExpTree* _right){
    node_list[new_node_index].c = _c;
    node_list[new_node_index].left = _left;
    node_list[new_node_index].right = _right;
    return node_list + (new_node_index++);
}

int main(){
    int T; cin >> T;
    while(T--){
        string input; cin >> input;
        new_node_index = 0;
        VEP v;
        for(string::iterator i=input.begin();i!=input.end();i++){
            if(islower(*i)){
                v.push_back(new_node(*i, NULL, NULL));
            }
            else{
                ExpTree* right = *v.rbegin(); v.pop_back();
                ExpTree* left = *v.rbegin(); v.pop_back();
                v.push_back(new_node(*i, left, right));
            }
        }
        VVEP vv(1, VEP(1, *v.rbegin()));
        while(true){
            VEP new_line;
            for(VEP::iterator i=vv.rbegin()->begin();i!=vv.rbegin()->end();i++){
                if((*i)->left) new_line.push_back((*i)->left);
                if((*i)->right) new_line.push_back((*i)->right);
            }
            if(new_line.empty()) break;
            else vv.push_back(new_line);
        }
        for(VVEP::reverse_iterator i=vv.rbegin();i!=vv.rend();i++){
            for(VEP::reverse_iterator j=i->rbegin();j!=i->rend();j++){
                printf("%c", (*j)->c);
            }
        }
        printf("\n");
    }
}
