#include "linked_list.hpp" 
#include <iostream>

template <typename T>
void runLinkedListTests() {
    // Create an instance of the linked_list class
    linked_list<T> myList;

    // Test push_front and push_back
    myList.push_front(1);
    myList.push_front(2);
    myList.push_back(3);
    myList.push_back(4);

    std::cout << "Size after push_front and push_back: " << myList.size() << std::endl; // Expect: 4

    // Test pop_front and pop_back
    myList.pop_front();
    myList.pop_back();

    std::cout << "Size after pop_front and pop_back: " << myList.size() << std::endl; // Expect: 2

    // Test empty and size
    std::cout << "Is list empty: " << (myList.empty() ? "true" : "false") << std::endl; // Expect: false
    std::cout << "List size: " << myList.size() << std::endl; // Expect: 2

    // Test front and back
    std::cout << "Front element: " << myList.front() << std::endl; // Expect: 2
    std::cout << "Back element: " << myList.back() << std::endl;   // Expect: 3

    // Test swap
    linked_list<T> anotherList;
    anotherList.push_back(5);
    anotherList.push_back(6);

    myList.swap(anotherList);

    std::cout << "Size after swap: " << myList.size() << std::endl; // Expect: 2

    // Test resize
    myList.resize(3);
    std::cout << "Size after resize: " << myList.size() << std::endl; // Expect: 3

    // Test insert and erase
    myList.insert(1, 10);
    myList.insert(0, 20);

    std::cout << "Front after inserts: " << myList.front() << std::endl; // Expect: 20

    T erasedData = myList.erase(&myList.front());
    std::cout << "Erased data: " << erasedData << std::endl; // Expect: 20

    std::cout << "Size after insert and erase: " << myList.size() << std::endl; // Expect: 4
}

int main() {
    // Run tests for int
    runLinkedListTests<int>();

    return 0;
}
