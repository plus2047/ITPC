// poj2356_Find_a_Multiple_map_TLE.cpp

// 使用高级数据结构的解法，不依赖鸽笼原理，对输入数据没有个数限制。
// 其基本思路是，既然 sum[i] 最多有 N 个取值，不妨对于每个新输入数据，穷举能够到达的 sum
// 最坏速度 O(n^2) 最坏情况发生在输入全都是 1 时。
// 然而 TLE 了

#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Footprint{
    int from_sum;
    int add_with;
};
typedef map<int, Footprint> Path;

void print(Path& sum_with_path, int N){
    Footprint f = sum_with_path[N];
    vector<int> ans;
    while(f.add_with){
        ans.push_back(f.add_with);
        f = sum_with_path[f.from_sum];
    }
    int s = (int)ans.size();
    printf("%d\n", s);
    for(int i=0;i<s;i++){
        printf("%d\n", ans[i]);
    }
}

int main(){
    int N; scanf("%d", &N);
    int num[N];
    for(int i=0;i<N;i++){ scanf("%d", num+i); }

    Path sum_path;
    sum_path[0] = Footprint();

    for(int i=0;i<N;i++){
        Path _sum_path;
        for(Path::iterator it=sum_path.begin();it!=sum_path.end();it++){
            int sum = it->first + num[i];
            Footprint _footprint = Footprint();
            _footprint.from_sum = it->first;
            _footprint.add_with = num[i];
            if(sum % N == 0){
                sum_path[N] = _footprint;
                print(sum_path, N);
                return 0;
            }
            _sum_path[sum] = _footprint;
        }
        sum_path.insert(_sum_path.begin(), _sum_path.end());
    }
}
