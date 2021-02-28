/**
* @mainpage
* @section intro Introduction
*
* The implementation of a "Queue" and a "Stack" based on a "Advanced Singly Linked List".
* 
* @section objective Assignment Objective
* In this assignment an Abstract Data Type of an "Advanced Singly Linked List" shall be implemented against 
* the defined common interface of a list. This interface is declared within file 'list.h'. It is intended
* to be used by applications or other libraries and aims to abstract the 'list' functionality as far as possible.
*
* Based on the implementation of that list, the two major goals, 'Queue' and 'Stack' shall be implemented.
*
* The term 'advanced' in 'Advanced Singly Linked List' refers to the members of the list data:
* the list shall have 
* - the pointer to the list head node, 
* - the pointer to the list tail, and 
* - the size as its members.
* 
* **Configuration**
*
* There is no configuration required.
*
* @section assignment Assignment
* The 'Advanced Singly Linked List' shall be implemented in file 'advanced_singly_linked_list.c'. The corresponding header file
* includes the common interface 'list.h' but does not add functions by its own.
* 
* The 'Queue' shall implement the interface given in 'queue.h' in file 'queue.c'. It shall make use of the linked list.
*
* The 'Stack' shall implement the interface given in 'stack.h' in file 'stack.c'. It shall make use of the linked list.
*
* The library 'allocator' is provided for memory allocation functionality that integrates with unit testing. Behind the facade,
* allocats memory dynamically similar to `malloc`. Allocated memory must be freed when it is not used anymore. The 'allocator'
* library must be used for memory alloction operations, otherwise unit tests will fail.
* 
*
* -# Implement 'advanced_singly_linked_list.c' against interface indirectly declared in 'list.h':
*    Note that some functions in list.h are commented. Those functions are not required for implementing Queue or Stack.
*    It is allowed to reuse the implementation of the 'simple_singly_linked_list' of an earlier assignment and 
*    turn it into an advanced singly linked list. Insertion at head and tail as well removal at head MUST have O(1)!
*
*    Make the program and tests compile: Implement all functions in all relevant files declared in the headers 
*    EMTPY (return nothing, 0, false, ... as required).
*   - All unit tests shall run but FAIL after this step
*   - **--COMMIT--**
*
* -# Implement the empty functions to make the unit tests pass one by one.
*   - Because unit tests depend on more than one function, it is a good idea to implement
*     all `obtain`, `release`, and `get_size` functions before running the tests.
*
*   - The purpose of a function is specified as API documentation within the header files.
*   - Obey comments in source files. Run the unit tests frequently and fix failures.
*   - **--COMMIT-- after each implemented function.**
*
* Main driver is not required in this assignment.
*
* @section notes Notes
* -# Again: Earlier implemenation of 'simple singly linked list` may be reused but MUST be transformed
*    into an 'advanced singly linked list'.
* -# make cleantest: This new make target for clearing the console, building, and running unit test is available.
* -# Sometimes changes are not properly detected by incremental builds. If something very strange 
*    happens during compilation, try to run `make clean` followed by `make` to start a clean build.
*    This approach is also recommended after everthing is done, because some compiler warning appears
*    only in clean builds. 
*/