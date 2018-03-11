//
// Created by Xu Jiahao on 15/02/2018.
//

#ifndef ITPC_BIT_ALGORITHM_H
#define ITPC_BIT_ALGORITHM_H

// warning: (x & (x - 1)) == 0 cannot be write as x & (x - 1) == 0
// unsigned algorithm can be used to int
inline bool isPowerOfTwo(unsigned x) { return x != 0 && (x & (x - 1)) == 0; }
inline bool isPowerOfTwo(int x) { return x != 0 && (x & -x) == x; }

inline int lowBit(int x) { return x&(-x); }

#include <cstdio>
void testBitAlgorithm(){
    for(int x=0;x<=8;x++) {
        printf("int %d is power of two: %d\n", x, isPowerOfTwo(x));
    }
    for(unsigned x=0;x<=8;x++) {
        printf("unsigned %u is power of two: %d\n", x, isPowerOfTwo(x));
    }
    for(int x=0;x<=8;x++){
        printf("lowBit of %d is : %d\n", x, lowBit(x));
    }
}

#endif //ITPC_BIT_ALGORITHM_H
