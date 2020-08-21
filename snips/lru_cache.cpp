#include <list>
#include <map>
#include <iostream>
using namespace std;

template <typename Key, typename Val>
struct LruCache {
    typedef std::list<std::pair<Key, Val> > Queue;
    std::size_t capacity;
    std::map<Key, typename Queue::iterator> tab;
    Queue queue;

   public:
    LruCache(std::size_t capacity) : capacity(capacity) {}

    bool has(const Key& key) { return tab.count(key); }

    void touch(const Key& key) { queue.splice(queue.end(), queue, tab[key]); }

    void erase(const Key& key) {
        auto iter = tab[key];
        tab.erase(key), queue.erase(iter);
    }

    const Val& get(const Key& key) {
        touch(key);
        return tab[key]->second;
    }

    void set(const Key& key, const Val& val) {
        if (tab.count(key)) {
            touch(key);
            tab[key]->second = val;
        } else {
            if (tab.size() >= capacity) erase(queue.front().first);
            tab[key] = queue.insert(queue.end(), std::make_pair(key, val));
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
        cout << cache.tab.size() << ' ' << cache.queue.size() << endl;
    }
    cout << "finished input" << endl;

    for (int i = 0; i < 10; i++) {
        if (cache.has(i)) {
            printf("%d\n", cache.get(i).val);
        }
    }
}