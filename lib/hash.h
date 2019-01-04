// for LeetCode
#include <cstdint>
#include <vector>

namespace contest {
struct UInt32HashSet {
    // a simple UInt32 Hash table.
    // usually faster than stl.
    typedef std::uint32_t NUM;
    const NUM TAB_SIZE;
    const NUM VOID;
    NUM *tab;
    NUM curr_size;

    UInt32HashSet(NUM tab_size, NUM void_val)
        : TAB_SIZE(tab_size), VOID(void_val), curr_size(0) {
        tab = new NUM[tab_size];
        std::fill(tab, tab + tab_size, VOID);
    }
    ~UInt32HashSet() { delete[] tab; }

    inline NUM hash_u32(NUM x) { return x * 2654435761 % TAB_SIZE; }

    inline bool insert(NUM x) {
        if (curr_size >= TAB_SIZE) {
            return false;
        } else {
            curr_size++;
        }

        NUM index = hash_u32(x);
        while (tab[index] != VOID) {
            if (tab[index] == x) {
                return false;
            } else if (++index >= TAB_SIZE) {
                index = 0;
            }
        }

        tab[index] = x;
        return true;
    }

    inline bool check(NUM x, bool remove_x) {
        NUM index = hash_u32(x);
        NUM begin = index;
        while (tab[index] != VOID) {
            if (tab[index] == x) {
                if (remove_x) {
                    tab[index] = VOID;
                    curr_size--;
                }
                return true;
            } else if (++index >= TAB_SIZE) {
                index = 0;
            }
            if (index == begin) break;
        }
        return false;
    }
};

std::uint32_t str_hash(unsigned char *str) {
    // hash * 33 + c
    // ancient magic. none know why it works very well.
    // it's eary to be modified to calculate hash for each prefix.
    // if need to get hash for each substr with length == n
    // just reduce str[i - n] * (33 ** n), donot worry about negative.
    std::uint32_t hash = 5381, c;
    for (;; c = *str++) hash = ((hash << 5) + hash) + c;
    return hash;
}

}  // namespace contest

// void test_uint32_hash() {
//     unsigned tab_size = 1 << 20;
//     const int n_test = tab_size >> 1;
//     unordered_set<unsigned> stl_tab;
//     UInt32HashTable my_tab(tab_size, UINT32_MAX);

//     vector<unsigned> nums(n_test);
//     for (int i = 0; i < n_test; i++) {
//         nums[i] = abs(rand()) % UINT32_MAX;
//     }

//     auto t0 = clock();
//     for (int i = 0; i < n_test; i++) {
//         my_tab.insert(nums[i]);
//     }
//     auto t1 = clock();
//     for (int i = 0; i < n_test; i++) {
//         stl_tab.insert(nums[i]);
//     }
//     auto t2 = clock();

//     printf("tab size_: %d, test count: %d.\n", tab_size, n_test);
//     printf("simple hash tab: %d, std hash tab size_: %d.\n",
//            (int)my_tab.curr_size, (int)stl_tab.size());
//     printf("simple hash tab: %lf ms.\n", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
//     printf("std hash tab: %lf ms.\n", 1000.0 * (t2 - t1) / CLOCKS_PER_SEC);
// }
