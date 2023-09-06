#ifndef SOLL
#define SOLL

#include "node.hpp"
#include <stdexcept>
#include <iostream>

template <typename T>
class self_organizing_linked_list {
private:
    node<T>* m_head;
    node<T>* m_tail;
    node<T>* m_asc_head;
    node<T>* m_desc_head;
public:
    self_organizing_linked_list();

    self_organizing_linked_list(const self_organizing_linked_list<T>& other);
    self_organizing_linked_list<T>& operator=(const self_organizing_linked_list<T>& other);

    self_organizing_linked_list(self_organizing_linked_list<T>&& other);
    self_organizing_linked_list<T>& operator=(self_organizing_linked_list<T>&& other);

    ~self_organizing_linked_list();

    void clear() noexcept;

    void push_front(const T& value);
    void push_back(const T& value);

    void pop_front();
    void pop_back();

    bool empty() const noexcept;

    T& front() const;
    T& back() const;

    T* begin() noexcept;
    T* end() noexcept;

    void swap(self_organizing_linked_list& other) noexcept;

    void insert(int pos, const T& value);
    void erase(int pos);

    void print();
    void print_asc();
    void print_desc();

};

// ctor
template <typename T>
self_organizing_linked_list<T>::self_organizing_linked_list() 
        : m_head{nullptr}
        , m_tail{nullptr}
        , m_asc_head{nullptr}
        , m_desc_head{nullptr}
{
}

// copy ctor
template <typename T>
self_organizing_linked_list<T>::self_organizing_linked_list(const self_organizing_linked_list<T>& other) 
        : m_head{nullptr}
        , m_tail{nullptr}
        , m_asc_head{nullptr}
        , m_desc_head{nullptr}
{
    node<T>* otherCurrent = other.m_head;
    while (otherCurrent) {
        node<T>* newNode = new node<T>{otherCurrent->m_data, nullptr, nullptr, nullptr, nullptr};

        if (!m_head) {
            m_head = newNode;
            m_tail = newNode;
        } else {
            m_tail->m_next = newNode;
            newNode->m_prev = m_tail;
            m_tail = newNode;
        }

        otherCurrent = otherCurrent->m_next;
    }
}

template <typename T>
self_organizing_linked_list<T>& self_organizing_linked_list<T>::operator=(const self_organizing_linked_list<T>& other) {
    if (this != &other) {
        clear();

        node<T>* other_current = other.m_head;
        while (other_current != nullptr) {
            push_back(other_current->m_data);
            other_current = other_current->m_next;
        }
    }
    return *this;
}

// move ctor
template <typename T>
self_organizing_linked_list<T>::self_organizing_linked_list(self_organizing_linked_list<T>&& other) 
        : m_head{other.m_head}
        , m_tail{other.m_tail}
        , m_asc_head{other.m_asc_head}
        , m_desc_head{other.m_desc_head}
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_asc_head = nullptr;
    other.m_desc_head = nullptr;
}

// move assignment operator
template <typename T>
self_organizing_linked_list<T>& self_organizing_linked_list<T>::operator=(self_organizing_linked_list<T>&& other) {
    if(this != &other) {
        swap_node(m_head, other.m_head);
        swap_node(m_tail, other.m_tail);
        swap_node(m_asc_head, other.m_asc_head);
        swap_node(m_desc_head, other.m_desc_head);
    }
    return *this;
}

template <typename T>
self_organizing_linked_list<T>::~self_organizing_linked_list() {
   clear();
}

template <typename T>
void self_organizing_linked_list<T>::clear() noexcept {
    node<T>* cur = m_head;
    while(cur != nullptr) {
        node<T>* tmp = cur->m_next;
        delete cur;
        cur = tmp;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_asc_head = nullptr;
    m_desc_head = nullptr;
}

template <typename T>
void self_organizing_linked_list<T>::push_front(const T& value) {
    node<T>* tmp = new node<T>{value, nullptr, nullptr, nullptr, nullptr};

    if(m_head == nullptr) {
        m_head = tmp;
        m_tail = tmp;
        m_asc_head = tmp;
        m_desc_head = tmp;
    } else if(m_head->m_next == nullptr) {
        tmp->m_next = m_head;
        m_head->m_prev = tmp;

        if(tmp->m_data > m_head->m_data) {
            m_head->m_asc = tmp;
            tmp->m_desc = m_head;
            m_desc_head = tmp;
            
        } else {
            m_head->m_desc = tmp;
            tmp->m_asc = m_head;
            m_asc_head = tmp;
        }
        m_head = tmp;
    } else {
        tmp->m_next = m_head;
        m_head->m_prev = tmp;
        if(m_asc_head->m_data >= value) {
            tmp->m_asc = m_asc_head;
            m_asc_head->m_desc = tmp;
            m_asc_head = tmp;
            m_head = tmp;
            return;
        } else if(m_desc_head->m_data <= value) {
            m_desc_head->m_asc =tmp;
            tmp->m_desc = m_desc_head;
            m_desc_head = tmp;
            m_head = tmp;
            return;
        }

        node<T>* cur = m_asc_head;

        while(cur->m_data < tmp->m_data && cur->m_asc != nullptr) {
            cur = cur->m_asc;
        }

        cur->m_desc->m_asc = tmp;
        tmp->m_desc = cur->m_desc;
        cur->m_desc = tmp;
        tmp->m_asc = cur;  

        m_head = tmp;    
    }  
}

template <typename T>
void self_organizing_linked_list<T>::push_back(const T& value) {
    node<T>* tmp = new node<T>{value, nullptr, nullptr, nullptr, nullptr};

    if(m_head == nullptr) {
        m_head = tmp;
        m_tail = tmp;
        m_asc_head = tmp;
        m_desc_head = tmp;
    } else if(m_head->m_next == nullptr) {
        m_head->m_next = tmp;
        tmp->m_prev = m_head;

        if(tmp->m_data > m_head->m_data) {
            m_head->m_asc = tmp;
            tmp->m_desc = m_head;
            m_desc_head = tmp;            
        } else {
            m_head->m_desc = tmp;
            tmp->m_asc = m_head;
            m_asc_head = tmp;
        }
        m_tail = tmp;
    } else {
        m_tail->m_next = tmp;
        tmp->m_prev = m_tail;
        if(m_asc_head->m_data >= value) {
            tmp->m_asc = m_asc_head;
            m_asc_head->m_desc = tmp;
            m_asc_head = tmp;
            m_tail = tmp;
            return;
        } else if(m_desc_head->m_data <= value) {
            m_desc_head->m_asc =tmp;
            tmp->m_desc = m_desc_head;
            m_desc_head = tmp;
            m_tail = tmp;
            return;
        }

        node<T>* cur = m_asc_head;

        while(cur->m_data < tmp->m_data && cur->m_asc != nullptr) {
            cur = cur->m_asc;
        }

        cur->m_desc->m_asc = tmp;
        tmp->m_desc = cur->m_desc;
        cur->m_desc = tmp;
        tmp->m_asc = cur;  

        m_tail = tmp;    
    }
    
}

template <typename T>
void self_organizing_linked_list<T>::pop_front() {
    if(m_head == nullptr) {
        return;
    }

    if(m_head->m_desc) {
        m_head->m_desc->m_asc = m_head->m_asc;
    }

    if(m_head->m_asc) {
        m_head->m_asc->m_desc = m_head->m_desc;
    }

    if(m_asc_head == m_head) {
        m_asc_head = m_asc_head->m_asc;
    }

    if(m_desc_head == m_head) {
        m_desc_head = m_desc_head->m_desc;
    }

    m_head->m_asc = nullptr;
    m_head->m_desc = nullptr;
    m_head->m_next->m_prev = nullptr;

    node<T>* tmp = m_head->m_next;
    delete m_head;
    m_head = tmp;

}

template <typename T>
void self_organizing_linked_list<T>::pop_back() {
    if(m_tail == nullptr) {
        return;
    }

    if(m_tail->m_desc) {
        m_tail->m_desc->m_asc = m_tail->m_asc;
    }

    if(m_tail->m_asc) {
        m_tail->m_asc->m_desc = m_tail->m_desc;
    }

    if(m_asc_head == m_tail) {
        m_asc_head = m_asc_head->m_asc;
    }

    if(m_desc_head == m_tail) {
        m_desc_head = m_desc_head->m_desc;
    }

    if(m_head == m_tail) {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        node<T>* tmp = m_tail->m_prev;
        tmp->m_next = nullptr;
        delete m_tail;
        m_tail = tmp;
    }

}

template <typename T>
bool self_organizing_linked_list<T>::empty() const noexcept {
    if(m_head == nullptr) {
        return true;
    }
    return false;
}

template <typename T>
T& self_organizing_linked_list<T>::front() const {
    if (m_head == nullptr) {
        throw std::runtime_error("The list is empty");
    }

    return m_head->m_data;
}

template <typename T>
T& self_organizing_linked_list<T>::back() const {
    if(m_head == nullptr) {
        throw std::runtime_error("The list is empty"); 
    }

    node<T>* cur = m_head;
    while(cur->m_next != nullptr) {
        cur = cur->m_next;
    }

    return cur->m_data;
}

template <typename T>
T* self_organizing_linked_list<T>::begin() noexcept {
    return m_head;
}

template <typename T>
T* self_organizing_linked_list<T>::end() noexcept {
    node<T>* cur = m_head;
    while(cur->m_next != nullptr) {
        cur = cur->next;
    }

    return cur;
}

template <typename T>
void self_organizing_linked_list<T>::swap(self_organizing_linked_list& other) noexcept {
    swap_node(m_head, other.m_head);
    swap_node(m_tail, other.m_tail);
    swap_node(m_asc_head, other.m_asc_head);
    swap_node(m_desc_head, other.m_desc_head);
}

template <typename T>
void swap_node(node<T>*& obj1, node<T>*& obj2) {
    node<T>* tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

template <typename T>
void self_organizing_linked_list<T>::insert(int pos, const T& value) {
    if(pos < 0) {
        return;
    }

    if(pos == 0) {
        push_front(value);
        return;
    }

    int size = 0;
    node<T>* cur = m_head;
    while(cur) {
        ++size;
        cur = cur->m_next;
    }

    if(pos > size) {
        return;
    }

    if(pos == size) {
        push_back(value);
        return;
    }

    node<T>* tmp = new node<T>{value, nullptr, nullptr, nullptr, nullptr};

    cur = m_head;
    while(pos != 1) {
        --pos;
        cur = cur->m_next;
    }

    cur->m_next->m_prev = tmp;
    tmp->m_next = cur->m_next;
    cur->m_next = tmp;
    tmp->m_prev = cur;

    cur = m_asc_head;
    while(cur->m_data <= value && cur->m_asc != nullptr) {
        cur = cur->m_asc;
    }

    cur->m_desc->m_asc = tmp;
    tmp->m_desc = cur->m_desc;
    cur->m_desc = tmp;
    tmp->m_asc = cur;  

}

template <typename T>
void self_organizing_linked_list<T>::erase(int pos) {
    if(pos < 0) {
        return;
    }

    if(pos == 0) {
        pop_front();
        return;
    }

    int size = 0;
    node<T>* cur = m_head;
    while(cur) {
        ++size;
        cur = cur->m_next;
    }

    if(pos > size) {
        return;
    }

    if(pos == size) {
        pop_back();
        return;
    }

    cur = m_head;
    while(pos != 0) {
        --pos;
        cur = cur->m_next;
    }

    cur->m_next->m_prev = cur->m_prev;
    cur->m_prev->m_next = cur->m_next;

    cur->m_asc->m_desc = cur->m_desc;
    cur->m_desc->m_asc = cur->m_asc;
}

template <typename T>
void self_organizing_linked_list<T>::print() {
    node<T>* cur = m_head;

    while(cur != nullptr) {
        std::cout << cur->m_data << " ";
        cur = cur->m_next;
    }
    std::cout << std::endl;
}

template <typename T>
void self_organizing_linked_list<T>::print_asc() {
    node<T>* cur = m_asc_head;

    while(cur != nullptr) {
        std::cout << cur->m_data << " ";
        cur = cur->m_asc;
    }
    std::cout << std::endl;
}

template <typename T>
void self_organizing_linked_list<T>::print_desc() {
    node<T>* cur = m_desc_head;

    while(cur != nullptr) {
        std::cout << cur->m_data << " ";
        cur = cur->m_desc;
    }
    std::cout << std::endl;
}

#endif
