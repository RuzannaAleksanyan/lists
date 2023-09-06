#include <iostream>
#include "self_organizing_linked_list.hpp" // Include the header file with your class definition

void runTests() {
    // Create an empty self-organizing linked list
    self_organizing_linked_list<int> list;

    // Test push_front and push_back
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_back(4);

    // Test print and print_asc
    std::cout << "List: ";
    list.print(); // Should print "List: 3 2 1 4"

    std::cout << "Asc List: ";
    list.print_asc(); // Should print "Asc List: 1 2 3 4"

    // Test print_desc
    std::cout << "Desc List: ";
    list.print_desc(); // Should print "Desc List: 4 3 2 1"

    // Test front and back
    std::cout << "Front: " << list.front() << std::endl; // Should print "Front: 3"
    std::cout << "Back: " << list.back() << std::endl;   // Should print "Back: 4"

    // Test pop_front and pop_back
    list.pop_front();
    list.pop_back();

    std::cout << "List after pop_front and pop_back: ";
    list.print(); // Should print "List: 2 1"

    // Test insert
    list.insert(1, 5);

    std::cout << "List after insert: ";
    list.print(); // Should print "List: 2 5 1"

    // Test erase
    list.erase(1);

    std::cout << "List after erase: ";
    list.print(); // Should print "List: 2 1"

    // Test copy constructor
    self_organizing_linked_list<int> copyList(list);
    std::cout << "Copy List: ";
    copyList.print(); // Should print "Copy List: 2 1"

    // // Test copy assignment operator
    self_organizing_linked_list<int> assignedList;
    assignedList = list;
    std::cout << "Assigned List: ";
    assignedList.print(); // Should print "Assigned List: 2 1"

    // Test move constructor
    self_organizing_linked_list<int> moveList(std::move(list));
    std::cout << "Move List: ";
    moveList.print(); // Should print "Move List: 2 1"

    // Test move assignment operator
    self_organizing_linked_list<int> movedList;
    movedList = std::move(assignedList);
    std::cout << "Moved List: ";
    movedList.print(); // Should print "Moved List: 2 1"
}

int main() {
    runTests();
    return 0;
}
