#ifndef NODE
#define NODE

template <typename T>
struct node
{
    node(const T& data = T{}, node* next = nullptr, node* prev = nullptr)
        : m_data(data)
        , m_next(next)
        , m_prev(prev) 
    {
    }

    T m_data;
    node* m_next;
    node* m_prev;
};

#endif
