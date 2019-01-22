#pragma once
#include <tuple>

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