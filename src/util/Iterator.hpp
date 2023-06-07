#pragma once

#include <list>

template <class T>
class Iterator {
private:
    std::list<T> values;
public:
    Iterator();
    template<typename it> Iterator(it);
    Iterator(T *begin, T *end);
    bool HasNext();
    const T Next();
    int Size();
};

#include "Iterator.tpp"