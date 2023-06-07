#pragma once

#include <unordered_map>
#include "Iterator.hpp"
#include <utility>

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

    ::Iterator<std::pair<K,V>> Iterator() {
        std::list<std::pair<K,V>> ls;
        for(std::pair<K,V> p : this->map) {
            ls.push_back(p);
        }
        return ::Iterator<std::pair<K,V>>(ls);
    }

    bool Contains(const K key) {
        return map.count(key);
    }
};