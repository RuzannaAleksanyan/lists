# Linked List
This repository contains a C++ implementation of a linked list data structure. A linked list is a linear data structure that consists of a sequence of elements, where each element points to the next element, forming a chain-like structure. This implementation provides basic functionality for managing and manipulating a list of elements.

## Features
- Basic Operations: The linked list supports fundamental operations such as insertion, deletion, and access of elements at both the front and the back of the list.
- Move Semantics: The implementation supports move semantics for efficient resource management when copying and assigning lists.
- Exception Handling: The implementation includes basic exception handling for out-of-range and invalid arguments, providing robust error handling during list manipulation.

## Usage
To use the linked list implementation in your C++ project, follow these steps:
- Include the linked_list.hpp header file in your source code.
- Create a linked_list object, specifying the data type for the list elements.
- Use the available methods to perform operations on the list, such as inserting, deleting, or accessing elements.
- Handle exceptions that may be thrown by the methods, such as std::out_of_range for invalid positions and std::invalid_argument for negative counts in the resize method.
- Remember to call the clear method when you are done using the list to free any allocated memory.
