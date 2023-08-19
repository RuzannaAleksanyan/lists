#include "doubly_linked_list.hpp"
#include <iostream>

template <typename T>
void runDoublyLinkedListTests() {
    // Create a doubly_linked_list
    doubly_linked_list<T> myList;

    // Test push_front and push_back
    myList.push_front(10);
    myList.push_back(20);
    myList.push_front(5);
    myList.push_back(30);

    std::cout << "Front: " << myList.front() << ", Back: " << myList.back() << std::endl; // Expect: 5, 30

    // Test pop_front and pop_back
    myList.pop_front();
    myList.pop_back();

    std::cout << "Front after pop_front: " << myList.front() << ", Back after pop_back: " << myList.back() << std::endl; // Expect: 10, 20

    // Test empty and size
    std::cout << "Is list empty? " << (myList.empty() ? "Yes" : "No") << ", Size: " << myList.size() << std::endl; // Expect: No, 2

    // Test begin and end
    std::cout << "Begin: " << *(myList.begin()) << ", End: " << *(myList.end()) << std::endl; // Expect: 10, 20

    // Test insert
    myList.insert(1, 15);
    std::cout << "Front after insert: " << myList.front() << ", Back after insert: " << myList.back() << std::endl; // Expect: 10, 20

    // Test erase
    myList.erase(myList.begin());
    myList.begin();

    // Test resize
    myList.resize(3);
    std::cout << "Size after resize: " << myList.size() << std::endl; // Expect: 3

    // Test swap
    doubly_linked_list<T> newList;
    newList.push_back(100);
    myList.swap(newList);
    newList.print();
    myList.print();

    std::cout << "Front after swap: " << myList.front() << ", Back after swap: " << myList.back() << std::endl; // Expect: 100, 100
}

int main() {
    runDoublyLinkedListTests<int>(); // Replace with your desired data type
    return 0;
}
