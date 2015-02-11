#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

class HashMap {
private:
    int MAX;
    vector<int> table;
    vector<bool> selecter;
    vector<long long> values;
    int hashing1(int);
    int hashing2(int);
    void expand();
    long long default_values;
public:
    HashMap();
    HashMap(int);
    void put(int, long long);
    long long get(int);
    bool remove(int);
    long long operator[](int);
};

HashMap::HashMap() {
    MAX = 16;
    table.assign(1<<MAX, -1);
    selecter.assign(1<<MAX, false);
    default_values = 0;
    values.assign(1<<MAX, default_values);
}

HashMap::HashMap(int capacity) {
    MAX = capacity;
    table.assign(1<<MAX, -1);
    selecter.assign(1<<MAX, false);
    default_values = 0;
    values.assign(1<<MAX, default_values);
}

void HashMap::put(int key, long long value) {
    int hash, activeKey = key, nextKey;
    bool activeSelect = true, nextSelect;
    long activeValue = value, nextValue;

    hash = hashing1(key);
    if(table[hash] == key) {
        values[hash] = value;
        return;
    }

    hash = hashing2(key);
    if(table[hash] == key) {
        values[hash] = value;
        return;
    }

    do {
        hash = activeSelect ? hashing1(activeKey) : hashing2(activeKey);

        nextKey = table[hash];
        nextSelect = selecter[hash];
        nextValue = values[hash];

        table[hash] = activeKey;
        selecter[hash] = !activeSelect;
        values[hash] = activeValue;

        activeKey = nextKey;
        activeSelect = nextSelect;
        activeValue = nextValue;

        if (activeKey==key && activeSelect) break;
    } while (activeKey != -1);

    if (activeKey == key) {
        expand();
        put(key, value);
    }
}

long long HashMap::get(int key) {
    int hash = hashing1(key);
    if(table[hash] == key) return values[hash];

    hash = hashing2(key);
    if(table[hash] == key) return values[hash];

    put(key, default_values);
    return default_values;
}

bool HashMap::remove(int key) {
    int hash = hashing1(key);
    if(table[hash] == key){
        table[hash] = -1;
        return true;
    }

    hash = hashing2(key);
    if(table[hash] == key){
        table[hash] = -1;
        return true;
    }

    return false;
}

int HashMap::hashing1(int x){
    x = (x+0x7ed55d16) + (x<<12);
    x = (x^0xc761c23c) ^ (x>>19);
    x = (x+0x165667b1) + (x<<5);
    x = (x+0xd3a2646c) ^ (x<<9);
    x = (x+0xfd7046c5) + (x<<3);
    x = (x^0xb55a4f09) ^ (x>>16);
    return x & 0x7fffffff>>(32-MAX);
}

int HashMap::hashing2(int x) {
    x -= (x<<6);
    x ^= (x>>17);
    x -= (x<<9);
    x ^= (x<<4);
    x -= (x<<3);
    x ^= (x<<10);
    x ^= (x>>15);
    return x & 0x7fffffff>>(32-MAX);
}

void HashMap::expand() {
    ++MAX;
    vector<int> oldTable = table;
    vector<long long> oldValues = values;

    table.reserve(1<<MAX);
    for (int i = 0; i < (1<<MAX); ++i)
        table[i] = -1;

    selecter.reserve(1<<MAX);
    values.reserve(1<<MAX);

    for(int i = 0; i < oldTable.size(); ++i){
        if(oldTable[i] == -1) continue;
        put(oldTable[i], oldValues[i]);
    }
}

long long HashMap::operator[](int key) {
    return get(key);
}

int main () {
    HashMap test;
    const int maxi = 1000000;
    for (int i = 0; i < maxi; ++i) {
        test.put(i, i);
    }
    return 0;
}
