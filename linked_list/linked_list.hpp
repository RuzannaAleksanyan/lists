#ifndef LINKEDLIST
#define LINKEDLIST

#include "node.hpp"

#include <utility>
#include <stdexcept>

template <typename T>
class linked_list {
private:
    node<T>* m_head;
    int m_size;
public:
    linked_list();

    linked_list(const linked_list<T>& other);
    linked_list<T>& operator=(const linked_list<T>& other);

    linked_list(linked_list<T>&& other);
    linked_list<T>& operator=(linked_list<T>&& other);

    ~linked_list();

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

    void swap(linked_list& other) noexcept;

    void resize(int count);

    void insert(const int pos, const T& value);
    T erase(const T* pos);
};

// ctor
template <typename T>
linked_list<T>::linked_list()
        : m_head(nullptr)
        , m_size(0)
{
}

//copy ctor
template <typename T>
linked_list<T>::linked_list(const linked_list<T>& other) 
        : m_head(nullptr)
        , m_size(0)
{
    node<T>* cur = other.m_head;

    while(cur != nullptr) {
        push_back(cur->m_data);
        cur = cur->m_next;
    }
}

// copy assignment operator
template <typename T>
linked_list<T>& linked_list<T>::operator=(const linked_list<T>& other)
{
    if(this != other) {
        clear();
        node<T>* cur = other->m_head;

        while(cur != nullptr) {
            push_back(cur->m_data);
            cur = cur->m_next;
        }
    }

    return *this;
}

// move ctor
template <typename T>
linked_list<T>::linked_list(linked_list<T>&& other) 
        : m_head(other.m_head)
        , m_size(other.m_size)
{
    other.m_head = nullptr;
    other.m_size = 0;
}

// move assignment operator
template <typename T>
linked_list<T>& linked_list<T>::operator=(linked_list<T>&& other) {
    if(this != &other) {
        swap_node(m_head, other.m_head);
        int tmp = m_size;
        m_size = other.m_size;
        other.m_size = tmp;
    }
}

// dtor
template <typename T>
linked_list<T>::~linked_list() {
    clear();
}

template <typename T>
void linked_list<T>::clear() noexcept {
    node<T>* cur = m_head;

    while(cur != nullptr) {
        node<T>* tmp = cur->m_next;
        delete cur;
        cur = tmp;
    }

    m_head = nullptr;
    m_size = 0;
}

template <typename T>
void linked_list<T>::push_front(const T& value) {
    node<T>* tmp = new node(value, m_head);

    m_head = tmp;
    ++m_size;
}

template <typename T>
void linked_list<T>::push_back(const T& value) {
    node<T>* tmp = new node<T>(value, nullptr);

    if (m_head == nullptr) {
        m_head = tmp;
    } else {
        node<T>* cur = m_head;
        while (cur->m_next != nullptr) {
            cur = cur->m_next;
        }
        cur->m_next = tmp;
    }

    ++m_size;
}

template <typename T>
void linked_list<T>::pop_front() {
    if( m_size == 0) {
        return;
    }

    node<T>* old_head = m_head;
    m_head = m_head->m_next;
    delete old_head;
    -- m_size;
}

template <typename T>
void linked_list<T>::pop_back() {
    if(m_head == nullptr) {
        return ;
    }

    if(m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
        --m_size;
        return;
    }

    node<T>* prev = nullptr;
    node<T>* cur = m_head;

    while(cur->m_next != nullptr) {
        prev = cur;
        cur = cur->m_next;
    }

    delete cur;
    prev->m_next = nullptr;
    --m_size;
}

template <typename T>
bool linked_list<T>::empty() const noexcept {
    return m_size == 0;
}

template <typename T>
int linked_list<T>::size() const noexcept {
    return m_size;
}

template <typename T>
T& linked_list<T>::front() const {
    if (m_head == nullptr) {
        throw std::runtime_error("The list is empty"); 
    }

    return m_head->m_data;
}

template <typename T>
T& linked_list<T>::back() const {
    if (m_head == nullptr) {
        throw std::runtime_error("The list is empty"); 
    }

    node<T>* cur = m_head;

    while(cur->m_next != nullptr) {
        cur = cur->m_next;
    }

    return cur->m_data;
}

template <typename T>
T* linked_list<T>::begin() noexcept {
    if (m_head == nullptr) {
        throw std::runtime_error("The list is empty"); 
    }

    return m_head;
}

template <typename T>
T* linked_list<T>::end() noexcept {
    if (m_head == nullptr) {
        throw std::runtime_error("The list is empty"); 
    }

    node<T>* cur = m_head;

    while(cur->m_next != nullptr) {
        cur = cur->m_next;
    }

    return cur->m_data;
}

template <typename T>
void linked_list<T>::swap(linked_list& other) noexcept {
    if(m_size == other.m_size) {
        swap_node(m_head, other.m_head);
    } else {
        return;
    }
}

template <typename T>
void linked_list<T>::resize(int count) {
    if (count < 0) {
        throw std::invalid_argument("resize: count cannot be negative");
    }

    if(count == m_size) {
        return;
    }

    if(count < m_size) {
        while(m_size > count) {
            pop_back();
        }
    } else {
        while(m_size < count) {
            push_back(T());
        }
    }
}

template <typename T>
void linked_list<T>::insert(const int pos, const T& value) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("insert: Position is out of range");
    }

    if(pos == m_size) {
        push_back(value);
        return;
    }

    node<T>* new_node = new node(value);

    if(pos == 0) {
        new_node->m_next = m_head;
        m_head = new_node;
    } else {
        node<T>* tmp = m_head;
        for (int i = 0; i < pos - 1; ++i) {
            tmp = tmp->m_next;
        }
        new_node->m_next = tmp->m_next;
        tmp->m_next = new_node;
    }

    ++m_size;
}

template <typename T>
T linked_list<T>::erase(const T* pos) {
    if (pos == nullptr) {
        throw std::invalid_argument("erase: pos is nullptr");
    }

    T value = *pos;

    if (m_head == nullptr) {
        throw std::runtime_error("erase: list is empty");
    }

    if (m_head->m_data == value) {
        node<T>* old_head = m_head;
        m_head = m_head->m_next;
        T data = old_head->m_data;
        delete old_head;
        --m_size;
        return data;
    }

    node<T>* prev = nullptr;
    node<T>* cur = m_head;

    while (cur != nullptr && cur->m_data != value) {
        prev = cur;
        cur = cur->m_next;
    }

    if (cur == nullptr) {
        throw std::invalid_argument("erase: value not found");
    }

    prev->m_next = cur->m_next;
    T data = cur->m_data;
    delete cur;
    --m_size;
    return data;
}

template <typename T>
void swap_node(node<T>*& list1, node<T>*& list2) {
    node<T>* tmp = list1;
    list1 = list2;
    list2 = tmp;
}
#endif
