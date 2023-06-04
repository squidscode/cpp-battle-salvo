#pragma once

#include <list>

template <class T>
class Iterator {
private:
    std::list<T> values;
public:
    Iterator(T *begin, T *end);
    bool HasNext();
    const T Next();
};

#include "./Iterator.tpp"