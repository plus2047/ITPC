#pragma once
// for LeetCode
#include <cstdint>
#include <vector>

namespace contest {
inline unsigned str_hash(unsigned char* str) {
    // hash * 33 + c
    // ancient magic. none know why it works very well.
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
    return unsigned(x) * 2654435761 % size;
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

    inline unsigned get_index(KEY key) {
        // if key in tab, return index of key
        // else return a void index for key
        KEY index = hash_u32(unsigned(key), SIZE);
        KEY begin = index;
        while (used[index]) {
            if (!removed[index] and keys[index] == key) return index;
            if (++index >= SIZE) index = 0;
        }
        return index;
    }

    inline bool insert(KEY key, VAL val) {
        if (curr_size >= MAX_ELEMET_NUM) return false;
        curr_size++;

        KEY index = get_index(key);
        if (used[index]) return false;

        keys[index] = key;
        vals[index] = val;
        return true;
    }

    inline bool get(KEY key, VAL& val) {
        unsigned idx = get_index(key);
        if (idx == SIZE) return false;
        val = vals[idx];
        return true;
    }

    inline bool erase(KEY key) {
        unsigned idx = get_index(key);
        if (idx == SIZE) return false;
        removed[idx] = true;
        return true;
    }
};
}  // namespace contest
