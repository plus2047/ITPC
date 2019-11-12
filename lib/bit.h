#pragma once

namespace contest {

// GCC / clang built in function to count 1 in binary. (fastest implement)
// for all those function, return type: int
// for unsigned int:
// int n =  __builtin_popcount(x)
// for unsigned long long int:
// int n = __builtin_popcountll(x)

// C++ STD
// int n = bitset<32>(x).count();


// warning: (x & (x - 1)) == 0 cannot be write as x & (x - 1) == 0
// unsigned algorithm can be used to int
inline bool isPowerOfTwo(unsigned x) { return x != 0 && (x & (x - 1)) == 0; }
inline bool isPowerOfTwo(int x) { return x != 0 && (x & -x) == x; }

inline int LSB(int x) { return x & (-x); }  // least significant bit

}  // namespace contest


// note: bit operator
//
// bool operator: and, or, xor, not
// bit operator: &, |, ^, ~
//
// get i-th bit of x: x & (1 << i)
// set i-th bit of x: x |= (1 << i)
// add mask: (x & 0x0000FF00)
//
// printf x as hex (width:8): printf("0x%08x", x)

// about: negative number
//
// 0x0000 - 1 == -1 == 0xFFFF
// - i == 0x0000 - i
