// poj2262_Goldbach's_Conjecture.cpp
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
using namespace std;

const int LIM = int(1E6);

vector<int> get_prime_list_flag(int less_than){
    vector<bool> flag((size_t)less_than, true);
    vector<int> prime;
    for(int num=2;num<less_than;num++){
        if(!flag[num]) continue;
        else{
            prime.push_back(num);
            for(int i=2;i*num<less_than;i++) flag[i*num] = false;
        }
    }
    return prime;
}

int main(){
    vector<int> prime = get_prime_list_flag(LIM);
    int n;
    while(scanf("%d", &n), n){
        for(int i=0;i<prime.size();i++){
            int b = n - prime[i];
            if(binary_search(prime.begin(), prime.end(), b)){
                printf("%d = %d + %d\n", n, prime[i], b);
                break;
            }
        }
    }
}