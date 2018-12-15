// http://poj.org/problem?id=1007

#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

char dna[200][100];
int n_sort[100];
int jump[100];
int N, M;

// get "unsorted number" with O(n^2) speed.
int get_unsorted_number_n2(const char *s){
    int c = 0;
    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            if(s[j] < s[i]) c++;
        }
    }
    return c;
}

// get "unsorted number" with O(n log n) speed.
// based on merge-sort.
int get_unsorted_number_nlogn(char *left, char *right){
    int count = 0, size = int(right - left);
    if(size < 2) return count;

    char *center = left + size / 2;
    count += get_unsorted_number_nlogn(left, center) + get_unsorted_number_nlogn(center, right);

    char swap[size];
    int index_1 = 0, index_2 = 0, index_merge=0, size_1 = int(center-left), size_2 = int(right-center);

    while(index_merge < size){
        if((left[index_1] <= center[index_2] || index_2 >= size_2) && index_1 < size_1){
            swap[index_merge] = left[index_1];
            index_1++;
        }
        else{
            swap[index_merge] = center[index_2];
            count += size_1 - index_1;
            index_2++;
        }
        index_merge++;
    }

    copy(swap, swap+size, left);
    return count;
}

int get_unsorted_number_nlogn(const char* s){
    char swap[N];
    copy(s, s+N, swap);
    return get_unsorted_number_nlogn(swap, swap+N);
}

int compare(const int& jump_a, const int& jump_b){
    if(n_sort[jump_a] == n_sort[jump_b]) return jump_a < jump_b;
    else return n_sort[jump_a] < n_sort[jump_b];
}

int main(){
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; i++){
        scanf("%s", dna[i]);
        n_sort[i] = get_unsorted_number_nlogn(dna[i]);
        jump[i] = i;
    }
    sort(jump, jump+M, compare);
    for(int i=0; i<M; i++){
        printf("%s\n", dna[jump[i]]);
    }
    return 0;
}
