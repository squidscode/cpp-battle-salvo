

template <class T>
Iterator<T>::Iterator() {}

template <class T>
template <typename it>
Iterator<T>::Iterator(it val) {
    auto fst = val.begin();
    while(fst != val.end()) {
        values.push_back(*fst);
        fst++;
    }
}

template <class T>
Iterator<T>::Iterator(T *begin, T *end) {
    while(begin != end) {
        values.push_back(*begin);
        begin++;
    }
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

template <class T>
int Iterator<T>::Size() {
    return values.size();
}