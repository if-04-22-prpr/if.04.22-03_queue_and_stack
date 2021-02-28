/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: S03
 * Title:			Queue Inteface
 * Author:			*/<your name>;/*
 * ----------------------------------------------------------
 * Description:
 * The declaration of a queue abstract data type.
 * ----------------------------------------------------------
 */


#include <stdbool.h>

/** The type of the integer queue: IntQueue. */

/**
 * Obtains ('creates') and provides a 'new' queue instance.
 * Any queue obtained via this function MUST be released using
 * function `release_queue()`.
 * 
 * Note: This function does not make any assumptions 
 * about how queue components, esp. nodes, are allocated.
 * 
 * @return IntQueue The queue instance or 0, if no queue could by instantiated.
 */
<type> queue_obtain();

/**
 * Releases a queue that was obtained earlier via function `obtain_queue`.
 * Released queues MUST NOT be used anymore.
 * 
 * Note: The implementation of this function does not make any assumptions
 * about the allocation method of queue elements, but MUST match the implementation
 * of function `obtain_queue` as its inverse function.
 * 
 * @param p_queue The pointer to the queue to release. The value of the pointer
 * is set to 0, if the queue was successfully released, otherwise it is left untouched.
 */
<type> queue_release(<params>);

/**
 * Determines whether or not the given queue is valid.
 * 
 * @param queue The queue to evaluate.
 * @return `True` if the queue is valid, false otherwise.
 */
<type> queue_is_valid(<params>);

/**
 * Determines whether or not the queue contains at least one item.
 * 
 * @param queue The queue to evaluate.
 * @return `False` if the queue contains one or more items, `true` otherwise.
 */
<type> queue_is_empty(<params>);

/**
 * Provides the number of values stored in the queue.
 * 
 * @param queue The queue to evaluate.
 * @return The number of values the queue contains.
 */
<type> queue_get_size(I<params>);

/**
 * Clears the given queue by removing all values from the queue.
 * 
 * @param queue The queue to clear.
 */
<type> queue_clear(<params>);

/**
 * Inserts the given value to the queue (as new tail).
 * 
 * @param queue The queue to which the value shall be appended.
 * @param value The value to append to the queue.
 */
<type> queue_enqueue(<params>);

/**
 * Provides the value that 'dequeue' would provided but WITHOUT removing 
 * this value from the queue.
 * 
 * @param queue The queue from which the value shall be peeked.
 * @return The next value or 0, if the queue is empty.
 */
<type> queue_peek(<params>);

/**
 * Provides AND removes the next value from the queue.
 * 
 * @param queue The queue from which the value shall be removed and returned.
 * @return The value or 0, if the queue is empty.
 */
<type> queue_dequeue(<params>);

