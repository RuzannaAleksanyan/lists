#ifndef LINKED_LIST_ITERATOR_HPP
#define LINKED_LIST_ITERATOR_HPP

#include "node.hpp"
#include <stdexcept> 

template <typename T>
class linked_list_iterator
{
private:
    node<T> *m_current;

public:
    explicit linked_list_iterator(node<T> *current) : m_current(current) {}

    linked_list_iterator &operator++();

    T &operator*() const;

    bool operator!=(const linked_list_iterator &other) const;
};

template <typename T>
linked_list_iterator<T>& linked_list_iterator<T>::operator++() {
    if (m_current != nullptr)
    {
        m_current = m_current->m_next;
    }
    return *this;
}

template <typename T>
T& linked_list_iterator<T>::operator*() const {
    if (m_current == nullptr)
    {
        throw std::runtime_error("Dereferencing end iterator");
    }
    return m_current->m_data;
}

template <typename T>
bool linked_list_iterator<T>::operator!=(const linked_list_iterator& other) const {
    return m_current != other.m_current;
}

#endif
