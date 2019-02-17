#pragma once

namespace contest {
// ===== Trie =====
// Trie use pointer index to store the info about string.
// the leaf point has no child pointer, so it use extra field
// to store info about whole string.
// be careful to use Trie. map<string> is usually enough.

const int TRIE_VOID_IDX = -1;  // void val for node index.
const int TRIE_VOID_VAL = -1;  // void val for node val field.
template <typename ITER, int sym_n>
struct Trie {
    // how to get child index from a iter.
    inline int get_idx(ITER c) { return *c - 'a'; }
    // how to update val for 'insert' func.
    inline void update_val(int& old, int val) { old = val; }

    struct Node {
        int child[sym_n], val;
        Node() : val(TRIE_VOID_VAL) {
            std::fill(child, child + sym_n, TRIE_VOID_IDX);
        }
    };

    std::vector<Node> nodes = {Node()};

    bool insert(ITER begin, ITER end, int val) {
        int root_index = 0;
        for (; begin != end; ++begin) {
            // dangerous: reference to variable saved in std container.
            int& child = nodes[root_index].child[get_idx(begin)];
            if (child == TRIE_VOID_IDX) {
                root_index = child = nodes.size();
                nodes.push_back(Node());
            } else {
                root_index = child;
            }
        }
        bool unseen = nodes[root_index].val == TRIE_VOID_VAL;
        update_val(nodes[root_index].val, val);
        return unseen;
    }

    // return true if it is a prefix.
    // and if it's a full match, save the string index into idx.
    bool check(ITER begin, ITER end, int& val) {
        int root_index = 0;
        for (; begin != end; ++begin) {
            int child = nodes[root_index].child[get_idx(begin)];
            if (child == TRIE_VOID_IDX) return false;
            root_index = child;
        }
        val = nodes[root_index].val;
        return true;
    }

    // use '.' to fuzzy match any char.
    // return true if full match any.
    bool dot_fuzzy(int root_index, ITER begin, ITER end) {
        while (begin != end) {
            if (*begin != '.') {
                int child = nodes[root_index].child[get_idx(begin)];
                if (child == TRIE_VOID_IDX) return false;
                root_index = child;
                begin++;
            } else {
                bool finded = false;
                begin++;
                for (int i = 0; i < sym_n; i++) {
                    int child = nodes[root_index].child[i];
                    if (child != TRIE_VOID_IDX) {
                        finded = check(child, begin, end);
                    }
                    if (finded) {
                        return true;
                    }
                }
                return false;
            }
        }
        return nodes[root_index].val != TRIE_VOID_VAL;
    }

    void print() {
        for (int i = 0; i < nodes.size(); i++) {
            std::printf("node id: %d, index: %d, child:", i, nodes[i].val);
            for (int j = 0; j < sym_n; j++) {
                std::printf("%d ", nodes[i].child[j]);
            }
            std::printf("\n");
        }
    }
};
}  // namespace contest
