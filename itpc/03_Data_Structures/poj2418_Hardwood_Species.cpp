// poj2418_Hardwood_Species.cpp

#include <map>
#include <string>
#include <iostream>

using namespace std;
typedef map<string,int> Count;

int main(){
    int count_sum = 0;
    Count count; // tree-name: count
    string name;
    while(getline(cin, name)){
        if(name.empty()) continue; // a boring question.
        count[name] ++;
        count_sum ++;
    }
    for(Count::iterator it=count.begin();it!=count.end();it++){
        printf("%s %.4lf\n", it->first.data(), it->second * 100.0 / count_sum);
    }
}
