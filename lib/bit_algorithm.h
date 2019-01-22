//
// Created by Xu Jiahao on 15/02/2018.
//

#ifndef ITPC_BIT_ALGORITHM_H
#define ITPC_BIT_ALGORITHM_H

// GCC / clang built in function to count 1 in binary.
// return type: int
// for unsigned int:
#define popcount(x) __builtin_popcount(x)
// for unsigned long long int:
#define popcountll(x) __builtin_popcountll(x)

namespace contest {

// warning: (x & (x - 1)) == 0 cannot be write as x & (x - 1) == 0
// unsigned algorithm can be used to int
inline bool isPowerOfTwo(unsigned x) { return x != 0 && (x & (x - 1)) == 0; }
inline bool isPowerOfTwo(int x) { return x != 0 && (x & -x) == x; }

inline int lowestBit(int x) { return x & (-x); }

// #include <cstdio>
// void testBitAlgorithm() {
//     for (int x = 0; x <= 8; x++) {
//         printf("int %d is power of two: %d\n", x, isPowerOfTwo(x));
//     }
//     for (unsigned x = 0; x <= 8; x++) {
//         printf("unsigned %u is power of two: %d\n", x, isPowerOfTwo(x));
//     }
//     for (int x = 0; x <= 8; x++) {
//         printf("lowBit of %d is : %d\n", x, lowestBit(x));
//     }
// }

}  // namespace contest
#endif  // ITPC_BIT_ALGORITHM_H

// bit operator
//
// bool operator: and, or, xor, not
// bit operator: &, |, ^, ~
//
// get i-th bit of x: x & (1 << i)
// set i-th bit of x: x |= (1 << i)
// add mask: (x & 0x0000FF00)
//
// printf x as hex (width:8): printf("0x%08x", x)

// Note: negative number
//
// 0x0000 - 1 == -1 == 0xFFFF
// - i == 0x0000 - i
