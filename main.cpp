// for programing contest
#include "lib/lazy_head.h"
#include "lib/itpc_math.h"
#include "lib/linear_algebra.h"
#include "lib/mod_p_field.h"

using namespace std;

typedef long long int lld;
typedef long long unsigned llu;

int main() {
    #ifdef __APPLE__
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
    #endif
    int n, p = 2179;
    for(int i = 0; i < 10; i ++){
        n = rand() % p;
        int rf = inv_mod_fermat(n, p);
        int re = _inv_mod_euclidean(n, p);
        printf("n: %d; p: %d; inv_f(n): %d; chk: %d\n", n, p, rf, rf * n % p);
        printf("n: %d; p: %d; inv_e(n): %d; chk: %d\n", n, p, re, re * n % p);
    }
}
