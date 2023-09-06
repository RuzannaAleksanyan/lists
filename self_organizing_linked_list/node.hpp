#ifndef NODE 
#define NODE

template <typename T>
struct node {
    node(const T& data = T{}, node* next = nullptr, node* prev = nullptr, node* asc = nullptr, node* desc = nullptr)
        : m_data(data)
        , m_next(next)
        , m_prev(prev) 
        , m_asc(asc)
        , m_desc(desc)
    {
    }

    T m_data;
    node* m_next;
    node* m_prev;
    node* m_asc;
    node* m_desc;
};

#endif
