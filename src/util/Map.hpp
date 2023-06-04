#pragma once

#include <unordered_map>

template <class K, class V>
class Map {
    std::unordered_map<K,V> map;
public:
    void Insert(const K key, const V value) {
        map.insert({key, value});
    }

    V Get(const K key) {
        return map[key];
    }

    V Remove(const K key) {
        return map.erase(map.find(key)).second;
    }

    bool Contains(const K key) {
        return map.count(key);
    }
};