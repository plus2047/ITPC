#pragma once
#include <cstdint>
#include <vector>

namespace contest {
inline unsigned hash_str(unsigned char* str) {
    // hash * 33 + c, ancient magic.
    unsigned hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *(str++);
    return hash;
}
// it's eary to be modified this string hash to calculate hash for each prefix.
// if need to get hash for each substr with length == n
// just reduce str[i - n] * (33 ** n), donot worry about negative.

inline unsigned hash_u32(unsigned x, unsigned size) {
    // hash function for unsigned 32
    // also can be used to other integer type.
    return x * 2654435761 % size;
}

template <unsigned SIZE, typename KEY, typename VAL>
struct HashMap {
    KEY keys[SIZE];
    VAL vals[SIZE];
    bool used[SIZE];
    bool removed[SIZE];
    unsigned curr_size;
    unsigned MAX_ELEMET_NUM = SIZE / 4 * 3;

    HashMap() {
        curr_size = 0;
        std::fill(used, used + SIZE, false);
        std::fill(removed, removed + SIZE, false);
    }

    inline bool update(KEY key, VAL val) {
        if (curr_size >= MAX_ELEMET_NUM) return false;

        unsigned index = hash_u32(unsigned(key), SIZE);
        while (used[index] and !removed[index] and keys[index] != key) {
            if (++index >= SIZE) index = 0;
        }

        keys[index] = key;
        vals[index] = val;
        if (!used[index]) {
            curr_size++;
            used[index] = true;
        } else {
            removed[index] = false;
        }
        return true;
    }

    inline bool get(KEY key, VAL& val) {
        KEY index = hash_u32(unsigned(key), SIZE);
        while (used[index]) {
            if (keys[index] == key and !removed[index]) {
                val = vals[index];
                return true;
            }
            if (++index >= SIZE) index = 0;
        }
        return false;
    }

    inline bool erase(KEY key) {
        KEY index = hash_u32(unsigned(key), SIZE);
        while (used[index]) {
            if (keys[index] == key and !removed[index]) {
                removed[index] = true;
                return true;
            }
            if (++index >= SIZE) index = 0;
        }
        return false;
    }
};
}  // namespace contest
