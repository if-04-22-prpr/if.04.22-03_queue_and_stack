/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: S03
 * Title:			Advanced Singly Linked List implementation
 * Author:			*/<your name>;/*
 * ----------------------------------------------------------
 * Description:
 * Implementation of an advanced singly linked list.
 * ----------------------------------------------------------
 */

/*
  Implementation notes:

  1) The 'ListData' struct of this linked list SHALL have
     - a pointer to the head node
     - a pointer to the tail node
     - the number of nodes (size)

  2) List and list node allocation: 
     Use functions `mem_alloc(…)` and `mem_free(…)`
     declared in `allocator.h`. DO NOT use `malloc(…)` and `free(…)` directly
     as unit tests will fail.

  3) Implement get_at, insert and insert_at, remove_at in a way that operations
     affecting head or tail are performed with O(1)!

  4) Use 'limits.h' to get maximum and minimum values for numeric types, if needed.

  5) Avoid code duplication wherever (reasonably) possible.
     This is valid for implementation of similar functions as well
     as for reoccurring code patterns, such as list iteration.
     Nevertheless, aim for efficiency, e.g. `remove_all` shall traverse 
     the list only once and not use `remove` as defined, because
     the later would start at the beginning of the list for each iteration.
*/

#include "advanced_singly_linked_list.h"

/* add includes as needed */

#include "config.h"
#include "allocator.h"

/** The type of list nodes */

/** The implementation of list node data */

/** The implementation of list data: head, tail, size! */


/* ===================================================================== */
/* private list functions */


static IntNode list_obtain_node(int value) {
}

static void list_release_node(IntNode* node) {
}


/* ===================================================================== */
