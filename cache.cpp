#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <iomanip>
using namespace std;

class Cache {
protected:
    int capacity;
    int hits;
    int misses;

public:
    Cache(int size) : capacity(size), hits(0), misses(0) {}
    
    virtual bool put(int key) = 0;
    
    pair<int, int> getStats() {
        return {hits, misses};
    }
    
    virtual vector<int> getCache() = 0;
    
    void resetStats() {
        hits = 0;
        misses = 0;
    }

    virtual void printStatus() {
        auto cache = getCache();
        cout << "\nCache status: ";
        for (int val : cache) {
            cout << val << " ";
        }
        cout << "\nHits: " << hits << " Misses: " << misses;
        if (hits + misses > 0) {
            double hitRate = (double)hits / (hits + misses) * 100;
            cout << fixed << setprecision(1) << "\nHit rate: " << hitRate << "%";
        }
        cout << endl;
    }
};

class FIFOCache : public Cache {
private:
    vector<int> cache;
    unordered_map<int, bool> present;

public:
    FIFOCache(int size) : Cache(size) {}
    
    bool put(int key) override {
        if (present[key]) {
            hits++;
            return true;
        }
        
        misses++;
        if (cache.size() >= capacity) {
            present[cache[0]] = false;
            cache.erase(cache.begin());
        }
        
        cache.push_back(key);
        present[key] = true;
        return false;
    }
    
    vector<int> getCache() override {
        return cache;
    }
};

class LRUCache : public Cache {
private:
    list<int> cache;
    unordered_map<int, list<int>::iterator> map;

public:
    LRUCache(int size) : Cache(size) {}
    
    bool put(int key) override {
        if (map.find(key) != map.end()) {
            hits++;
            cache.erase(map[key]);
            cache.push_back(key);
            map[key] = --cache.end();
            return true;
        }
        
        misses++;
        if (cache.size() >= capacity) {
            map.erase(cache.front());
            cache.pop_front();
        }
        
        cache.push_back(key);
        map[key] = --cache.end();
        return false;
    }
    
    vector<int> getCache() override {
        return vector<int>(cache.begin(), cache.end());
    }
};

int main() {
    cout << "\033[1;36m"; // Cyan text color for header
    cout << "Paging Algorithm Visualizer\n";
    cout << "=====================================\n";
    cout << "\033[0m"; // Reset text color

    int cacheSize = 3;
    vector<int> sequence = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    
    cout << "\033[1;33m"; // Yellow text color
    cout << "\nFIFO Test:\n";
    cout << "\033[0m"; // Reset text color
    
    FIFOCache fifo(cacheSize);
    for (int num : sequence) {
        cout << "\nAccessing: " << num;
        fifo.put(num);
        fifo.printStatus();
    }
    
    cout << "\033[1;33m"; // Yellow text color
    cout << "\nLRU Test:\n";
    cout << "\033[0m"; // Reset text color
    
    LRUCache lru(cacheSize);
    for (int num : sequence) {
        cout << "\nAccessing: " << num;
        lru.put(num);
        lru.printStatus();
    }
    
    return 0;
}