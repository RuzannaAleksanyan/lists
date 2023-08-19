#ifndef DOUBLYLINKEDLIST
#define DOUBLYLINKEDLIST

#include "node.hpp"

#include <utility>
#include <stdexcept>
#include <iostream>

template <typename T>
class doubly_linked_list
{
private:
    node<T>* m_head;
    node<T>* m_tail;
    int m_size;

public:
    doubly_linked_list();

    doubly_linked_list(const doubly_linked_list<T>& other);
    doubly_linked_list<T>& operator=(const doubly_linked_list<T>& other);

    doubly_linked_list(doubly_linked_list<T>&& other);
    doubly_linked_list<T>& operator=(doubly_linked_list<T>&& other);

    ~doubly_linked_list();

    void clear() noexcept;

    void push_front(const T& value);
    void push_back(const T& value);

    void pop_front();
    void pop_back();

    bool empty() const noexcept;
    int size() const noexcept;

    T& front() const;
    T& back() const;

    T* begin() noexcept;
    T* end() noexcept;

    void swap(doubly_linked_list& other) noexcept;

    void resize(int count);

    void insert(const int pos, const T& value);
    void erase(const T* pos);

    void print();

};

template <typename T>
void doubly_linked_list<T>::print() {
    node<T>* cur = m_head;
    if(m_size != 0) {
        while(cur->m_next != nullptr) {
            std::cout << cur->m_data << " ";
            cur = cur->m_next;
        }
        std::cout << cur->m_data << " ";
    }

    std::cout << std::endl;
}

// ctor
template <typename T>
doubly_linked_list<T>::doubly_linked_list()
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_size(0)
{
}

//copy ctor
template <typename T>
doubly_linked_list<T>::doubly_linked_list(const doubly_linked_list<T>& other)
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_size(0)
{
    node<T>* cur = other.m_head;
    while (cur != nullptr) {
        push_back(cur->m_data);
        cur = cur->m_next;
    }
}

// copy assignment operator
template <typename T>
doubly_linked_list<T>& doubly_linked_list<T>::operator=(const doubly_linked_list<T>& other)
{
    if (this != &other) {
        clear();
        node<T>* cur = other.m_head;
        while (cur != nullptr) {
            push_back(cur->m_data);
            cur = cur->m_next;
        }
    }

    return *this;
}

// move ctor
template <typename T>
doubly_linked_list<T>::doubly_linked_list(doubly_linked_list<T>&& other)
    : m_head(other.m_head)
    , m_tail(other.m_tail)
    , m_size(other.m_size)
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

// move assignment operator
template <typename T>
doubly_linked_list<T>& doubly_linked_list<T>::operator=(doubly_linked_list<T>&& other)
{
    if (this != & other) {
        swap_node(m_head, other.m_head);
        swap_node(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }
    return *this;
}

// dtor 
template <typename T>
doubly_linked_list<T>::~doubly_linked_list()
{
    clear();
}

template <typename T>
void doubly_linked_list<T>::clear() noexcept
{
    node<T>* cur = m_head;

    while (cur != nullptr) {
        node<T>* tmp = cur->m_next;
        delete cur;
        cur = tmp;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template <typename T>
void doubly_linked_list<T>::push_front(const T& value)
{
    node<T>* tmp = new node(value, m_head);

    if (m_head != nullptr) {
        m_head->m_prev = tmp;
        tmp->m_next = m_head;
    } else {
        m_tail = tmp;
    }

    m_head = tmp;
    ++m_size;
}

template <typename T>
void doubly_linked_list<T>::push_back(const T& value) {
    node<T>* tmp = new node<T>(value, nullptr, m_tail);

    if (m_tail != nullptr) {
        m_tail->m_next = tmp;
    } else {
        m_head = tmp;
    }

    m_tail = tmp;
    ++m_size;
}

template <typename T>
void doubly_linked_list<T>::pop_front()
{
    if (m_size == 0) {
        return;
    }

    node<T>* old_head = m_head;
    m_head = m_head->m_next;

    if (m_head != nullptr) {
        old_head->m_prev = nullptr;
    }
    else {
        m_tail = nullptr;
    }

    delete old_head;
    --m_size;
}

template <typename T>
void doubly_linked_list<T>::pop_back()
{
    if (m_size == 0) {
        return;
    }

    node<T>* old_tail = m_tail;

    if (m_size == 1) {
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        m_tail = m_tail->m_prev;
        m_tail->m_next = nullptr;
    }

    delete old_tail;
    --m_size;
}

template <typename T>
bool doubly_linked_list<T>::empty() const noexcept
{
    return m_size == 0;
}

template <typename T>
int doubly_linked_list<T>::size() const noexcept
{
    return m_size;
}

template <typename T>
T& doubly_linked_list<T>::front() const
{
    return m_head->m_data;
}

template <typename T>
T& doubly_linked_list<T>::back() const {
    return m_tail->m_data;
}

template <typename T>
T* doubly_linked_list<T>::begin() noexcept {
    if (m_head == nullptr) {
        return nullptr;
    }
    return &(m_head->m_data);
}

template <typename T>
T* doubly_linked_list<T>::end() noexcept {
    if (m_tail == nullptr) {
        return nullptr;
    }
    return &(m_tail->m_data);
}

template <typename T>
void doubly_linked_list<T>::swap(doubly_linked_list& other ) noexcept {

    swap_node(m_head, other.m_head);
    swap_node(m_tail, other.m_tail);
    
}

template <typename T>
void doubly_linked_list<T>::resize(int count)
{
    if (count < 0) {
        throw std::invalid_argument("resize: count cannot be negative");
    }

    if (count == m_size) {
        return; 
    }

    if (count < m_size) {
        while (m_size > count) {
            pop_back();
        }
    } else {
        while (m_size < count) {
            push_back(T()); 
        }
    }
}

template <typename T>
void doubly_linked_list<T>::insert(const int pos, const T& value) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("insert: Position is out of range");
    }

    if (pos == m_size) {
        push_back(value);
        return; 
    }

    node<T>* new_node = new node<T>(value);

    if (pos == 0) {
        new_node->m_next = m_head;
        m_head->m_prev = new_node;
        m_head = new_node;
    } else {
        node<T>* tmp = m_head;
        for (int i = 0; i < pos - 1; ++i) {
            tmp = tmp->m_next;
        }
        new_node->m_next = tmp->m_next;
        new_node->m_prev = tmp;
        tmp->m_next->m_prev = new_node;
        tmp->m_next = new_node;
    }

    m_size++;
}

template <typename T>
void doubly_linked_list<T>::erase(const T* pos) {
    if (pos == nullptr || m_size == 0) {
        return; 
    }

    node<T>* cur = m_head;
    while (cur != nullptr) {
        if (&(cur->m_data) == pos) {
            if (cur == m_head) {
                m_head = cur->m_next;
            }
            if (cur == m_tail) {
                m_tail = cur->m_prev;
            }
            if (cur->m_prev != nullptr) {
                cur->m_prev->m_next = cur->m_next;
            }
            if (cur->m_next != nullptr) {
                cur->m_next->m_prev = cur->m_prev;
            }
            delete cur;
            --m_size;
            break;  
        }
        cur = cur->m_next;
    }
}


template <typename T>
void swap_node(node<T>*& list1, node<T>*& list2) {
    node<T>* tmp = list1;
    list1 = list2;
    list2 = tmp;
}

#endif
