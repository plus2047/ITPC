```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <unordered_map>

// Dummy hash function for simplicity
unsigned hash_u32(unsigned key, unsigned size) {
    return key % size;
}

template <typename KEY, typename VAL>
struct HashMap {
    std::vector<KEY> keys;
    std::vector<VAL> vals;
    std::vector<char> used;
    std::vector<char> removed;
    unsigned capacity;
    unsigned size;
    unsigned max_size;

    HashMap(unsigned capacity):
        keys(capacity), 
        vals(capacity), 
        used(capacity), 
        removed(capacity),
        capacity(capacity),
        size(0),
        max_size(capacity * 4 / 3) {}

    inline bool update(KEY key, VAL val) {
        if (size >= max_size) return false;

        unsigned index = hash_u32(unsigned(key), capacity);
        while (used[index] && !removed[index] && keys[index] != key) {
            if (++index >= capacity) index = 0;
        }

        keys[index] = key;
        vals[index] = val;
        if (!used[index]) {
            size++;
            used[index] = true;
        } else {
            removed[index] = false;
        }
        return true;
    }

    inline bool get(KEY key, VAL& val) {
        unsigned index = hash_u32(unsigned(key), capacity);
        while (used[index]) {
            if (keys[index] == key && !removed[index]) {
                val = vals[index];
                return true;
            }
            if (++index >= capacity) index = 0;
        }
        return false;
    }

    inline bool erase(KEY key) {
        unsigned index = hash_u32(unsigned(key), capacity);
        while (used[index]) {
            if (keys[index] == key && !removed[index]) {
                removed[index] = true;
                return true;
            }
            if (++index >= capacity) index = 0;
        }
        return false;
    }
};

int test_flat_map() {
    constexpr int operations = 1'000'000;
    constexpr unsigned SIZE = operations * 2;

    HashMap<int, int> map(SIZE);

    std::srand(std::time(0));
    std::vector<int> keys;
    std::vector<int> vals;
    for (int i = 0; i < operations; i++) {
        int key = std::rand();
        int value = std::rand();
        keys.push_back(key);
        vals.push_back(value);
    }

    auto startInsertTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operations; i++) {
        map.update(keys[i], vals[i]);
    }
    auto endInsertTime = std::chrono::high_resolution_clock::now();
    auto insertDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endInsertTime - startInsertTime);
    std::cout << "Time taken for inserting 1 million elements: " << insertDuration.count() << " ms" << std::endl;

    auto startDeleteTime = std::chrono::high_resolution_clock::now();
    for (const int& key : keys) {
        map.erase(key);
    }
    auto endDeleteTime = std::chrono::high_resolution_clock::now();
    auto deleteDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endDeleteTime - startDeleteTime);
    std::cout << "Time taken for deleting 1 million elements: " << deleteDuration.count() << " ms" << std::endl;

    std::unordered_map<int, int> stl_map(SIZE);

    startInsertTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operations; i++) {
        stl_map[keys[i]] = vals[i];
    }
    endInsertTime = std::chrono::high_resolution_clock::now();
    insertDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endInsertTime - startInsertTime);
    std::cout << "Time taken for inserting 1 million elements: " << insertDuration.count() << " ms" << std::endl;

    startDeleteTime = std::chrono::high_resolution_clock::now();
    for (const int& key : keys) {
        stl_map.erase(key);
    }
    endDeleteTime = std::chrono::high_resolution_clock::now();
    deleteDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endDeleteTime - startDeleteTime);
    std::cout << "Time taken for deleting 1 million elements: " << deleteDuration.count() << " ms" << std::endl;

    std::vector<std::pair<int, int>> vec(operations);

    startInsertTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operations; i++) {
        vec[i] = {keys[i], vals[i]};
    }
    endInsertTime = std::chrono::high_resolution_clock::now();
    insertDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endInsertTime - startInsertTime);
    std::cout << "Time taken for inserting 1 million elements: " << insertDuration.count() << " ms" << std::endl;

    sort(vec.begin(), vec.end());

    startDeleteTime = std::chrono::high_resolution_clock::now();
    long long total = 0;
    for (int i = 0 ; i < operations; i++) {
        total += vec[i].second % (i + 1);
        vec[i] = {0, 0};
    }
    endDeleteTime = std::chrono::high_resolution_clock::now();
    deleteDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endDeleteTime - startDeleteTime);
    std::cout << "Time taken for deleting 1 million elements: " << deleteDuration.count() << " ms" << std::endl;
    std::cout << total << std::endl;

    return 0;
}

int main() {
    test_flat_map();
}
```

Time taken for inserting 1 million elements: 19 ms
Time taken for deleting 1 million elements: 15 ms
Time taken for inserting 1 million elements: 131 ms
Time taken for deleting 1 million elements: 112 ms
Time taken for inserting 1 million elements: 0 ms
Time taken for deleting 1 million elements: 2 ms


```java
import java.util.HashMap;
import java.util.Random;
import java.util.ArrayList;

public class Solution {
    public static void main(String[] args) {
        // Create a HashMap
        HashMap<Integer, Integer> map = new HashMap<>();

        // List to store keys for later removal
        ArrayList<Integer> keys = new ArrayList<>();
        ArrayList<Integer> vals = new ArrayList<>();

        // Number of operations
        int operations = 1_000_000;

        // Random number generator
        Random random = new Random();
        for (int i = 0; i < operations; i++) {
            int key = random.nextInt();
            int value = random.nextInt();
            keys.add(key);
            vals.add(value);
        }

        // Measure the time taken for inserting elements
        long startInsertTime = System.nanoTime();
        for (int i = 0; i < operations; i++) {
            map.put(keys.get(i), vals.get(i));
        }
        long endInsertTime = System.nanoTime();
        System.out.println("Time taken for inserting 1 million elements: " + (endInsertTime - startInsertTime) / 1_000_000 + " ms");

        // Measure the time taken for deleting elements
        long startDeleteTime = System.nanoTime();
        for (int key : keys) {
            map.remove(key);
        }
        long endDeleteTime = System.nanoTime();
        System.out.println("Time taken for deleting 1 million elements: " + (endDeleteTime - startDeleteTime) / 1_000_000 + " ms");
    }
}
```

Time taken for inserting 1 million elements: 181 ms
Time taken for deleting 1 million elements: 141 ms

```python
import random
import time

# Create a dictionary
data_map = {}

# List to store keys for later removal
keys = []
vals = []

# Number of operations
operations = 1_000_000
for _ in range(operations):
    key = random.randint(0, 10**9)
    value = random.randint(0, 10**9)
    keys.append(key)
    vals.append(value)

# Measure the time taken for inserting elements
start_insert_time = time.time()
for i in range(operations):
    data_map[keys[i]] = vals[i]
end_insert_time = time.time()
print(f"Time taken for inserting 1 million elements: {(end_insert_time - start_insert_time) * 1000:.2f} ms")

keys = list(set(keys))

# Measure the time taken for deleting elements
start_delete_time = time.time()
for key in keys:
    del data_map[key]
end_delete_time = time.time()
print(f"Time taken for deleting 1 million elements: {(end_delete_time - start_delete_time) * 1000:.2f} ms")
```

Time taken for inserting 1 million elements: 361.65 ms
Time taken for deleting 1 million elements: 277.37 ms