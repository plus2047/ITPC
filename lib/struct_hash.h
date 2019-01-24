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

    void clear() {
        curr_size = 0;
        std::fill(used, used + SIZE, false);
        std::fill(removed, removed + SIZE, false);
    }
    HashMap() { clear(); }

    inline bool update(KEY key, VAL val) {
        if (curr_size >= MAX_ELEMET_NUM) return false;

        KEY index = hash_u32(unsigned(key), SIZE);
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

namespace std {
// those tools is extended to std::tuple.
// so define them in namespace std.
template <typename TUPLE, size_t FIELD>
bool upper(const TUPLE& a, const TUPLE& b) {
    return std::get<FIELD>(a) > std::get<FIELD>(b);
}
template <typename TUPLE, size_t FIELD>
bool lower(const TUPLE& a, const TUPLE& b) {
    return std::get<FIELD>(a) < std::get<FIELD>(b);
}

// modern magic: hash implement for tuple.
template <class t>
inline void hash_combine(std::size_t& seed, t const& v) {
    seed ^= hash<t>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <class TUPLE, size_t index = std::tuple_size<TUPLE>::value - 1>
struct hash_value_impl {
    static void apply(size_t& seed, TUPLE const& tuple) {
        hash_value_impl<TUPLE, index - 1>::apply(seed, tuple);
        hash_combine(seed, get<index>(tuple));
    }
};

template <class TUPLE>
struct hash_value_impl<TUPLE, 0> {
    static void apply(size_t& seed, TUPLE const& tuple) {
        hash_combine(seed, get<0>(tuple));
    }
};

template <typename... TT>
struct hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const& tt) const {
        size_t seed = 0;
        hash_value_impl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};
}  // namespace std
