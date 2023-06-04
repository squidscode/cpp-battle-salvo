#pragma once

#include <list>

template <class T>
class Iterator {
private:
    std::list<T> values;
public:
    Iterator(T *begin, T *end) {
        while(begin != end) values.push_back(*begin);
    }

    bool HasNext() {
        return !values.empty();
    }

    const T Next() {
        T next = values.front();
        values.pop_front();
        return next;
    }
};