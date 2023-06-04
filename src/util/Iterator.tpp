#include "./Iterator.hpp"

template <class T>
Iterator<T>::Iterator(T *begin, T *end) {
    while(begin != end) values.push_back(*begin);
}

template <class T>
bool Iterator<T>::HasNext() {
    return !values.empty();
}

template <class T>
const T Iterator<T>::Next() {
    T next = values.front();
    values.pop_front();
    return next;
}