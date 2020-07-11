#pragma once
#include <cstdint>
#include <vector>

namespace contest {

// it's eary to be modified this string hash to calculate hash for each prefix.
// if need to get hash for each substr with length == n
// just reduce str[i - n] * (33 ** n), donot worry about negative.
inline unsigned hash_str(unsigned char* str) {
    // hash * 33 + c, ancient magic.
    unsigned hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *(str++);
    return hash;
}

// hash function for unsigned 32
// also can be used to other integer type.
inline unsigned hash_u32(unsigned x, unsigned size) {
    return x * 2654435761 % size;
}

}  // namespace contest