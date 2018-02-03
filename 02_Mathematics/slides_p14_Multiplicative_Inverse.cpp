// slides_p14_Multiplicative_Inverse.cpp
#include <cstdio>
#include <cmath>
#include <climits>
using namespace std;

int euclidean_gcd(int a, int b){
    while(b){
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int multiplicative_inverse(int n, int a){
    int aa_times = 1, an_times = 0, nn_times = 1, na_times = 0;
    while(a){
        int r = n % a, t = n / a;
        n = a;
        int na_times_new = aa_times;
        int nn_times_new = an_times;
        a = r;
        int aa_times_new = na_times - t * aa_times;
        int an_times_new = nn_times - t * an_times;
        aa_times = aa_times_new;
        an_times = an_times_new;
        na_times = na_times_new;
        nn_times = nn_times_new;
    }
    printf("%d %d %d %d\n", aa_times, an_times, na_times, nn_times);
    if(n == 1){
        return na_times;
    }
    else{
        return 0;
    }
}

int main(){
    printf("%d\n", multiplicative_inverse(19, 7));
}
