#include <list>
#include <map>
#include <iostream>
using namespace std;

// !!! this is not a good implement !!!
// !!! this is just a stupid try, I find that it's much harder than image.

template <typename Key, typename Val>
struct LruCache {
    typedef std::list<std::pair<Key, Val> > Que;
    Que que;
    std::map<Key, typename Que::iterator> tab;
    std::mutex mut;
    std::size_t capacity;

public:
    LruCache() : capacity(0) {}
    LruCache(std::size_t capacity) : capacity(capacity) {}

    std::size_t size() { return tab.size(); }
    bool full() { return tab.size() >= capacity; }
    bool has(const Key& key) { return tab.count(key); }
    Val& get(const Key& key) { return tab[key]->second; }

    void reserve(std::size_t capacity) {
        std::lock_guard<std::mutex> guard(mut);
        this->capacity = capacity;
    }

    void touch(const Key& key) {
        std::lock_guard<std::mutex> guard(mut);
        que.splice(que.end(), que, tab[key]);
    }

    void erase(const Key& key) {
        std::lock_guard<std::mutex> guard(mut);
        auto iter = tab[key];
        tab.erase(key), que.erase(iter);
    }

    void set(const Key& key, const Val& val) {
        if (tab.count(key)) {
            touch(key);
            tab[key]->second = val;
        } else {
            std::lock_guard<std::mutex> guard(mut);
            if (full()) {
                auto p = que.front();
                tab.erase(p.first), que.pop_front();
            }
            tab[key] = que.insert(que.end(), std::make_pair(key, val));
        }
    }
};

struct ST {
    int val;
    ST(int val): val(val) {
        printf("cons %d\n", val);
    }
    ~ST() {
        printf("dec %d\n", val);
    }
};

int main() {
    LruCache<int, ST> cache(5);
    for (int i = 0; i < 10; i++) {
        cache.set(i, ST(i));
        cout << cache.que.size() << ' ' << cache.tab.size() << endl;
    }
    cout << "finished input" << endl;

    for (int i = 0; i < 10; i++) {
        if (cache.has(i)) {
            printf("%d\n", cache.get(i).val);
        }
    }
}