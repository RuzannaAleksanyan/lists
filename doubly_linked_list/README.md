# Doubly Linked List
This repository contains a C++ implementation of a doubly linked list data structure. The doubly linked list is a linear data structure that consists of a sequence of elements, where each element points to both the previous and the next elements, forming a bidirectional connection. This implementation provides a flexible and efficient way to manage and manipulate a list of elements.

## Features
- Basic Operations: The doubly linked list supports essential operations like insertion, deletion, and access of elements at both the front and the back of the list.
- Move Semantics: The implementation supports move semantics for efficient resource management when copying and assigning lists.
- Resize and Manipulation: You can resize the list to a specified number of elements, and insert or erase elements at a given position.
- Exception Handling: The implementation includes basic exception handling for out-of-range and invalid arguments, providing robust error handling during list manipulation.

## Usage
To use the doubly linked list implementation in your C++ project, follow these steps:
- Include the doubly_linked_list.hpp header file in your source code.
- Create a doubly_linked_list object, specifying the data type for the list elements.
- Use the available methods to perform operations on the list, such as inserting, deleting, or accessing elements.
- Make sure to handle exceptions that may be thrown by the methods, such as std::out_of_range for invalid positions and std::invalid_argument for negative counts in the resize method.
- When you are done using the list, it is essential to call the clear method to free any allocated memory.
