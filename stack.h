/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: S03
 * Title:			Stack Inteface
 * Author:			*/<your name>;/*
 * ----------------------------------------------------------
 * Description:
 * The declaration of a stack abstract data type.
 * ----------------------------------------------------------
 */

/** The type of the integer stack: IntStack */

/**
 * Obtains ('creates') and provides a 'new' stack instance.
 * Any stack obtained via this function MUST be released using
 * function `release_stack()`.
 * 
 * Note: This function does not make any assumptions 
 * about how stack components, esp. nodes, are allocated.
 * 
 * @return IntStack The stack instance or 0, if no stack could by instantiated.
 */
<type> stack_obtain();

/**
 * Releases a stack that was obtained earlier via function `obtain_stack`.
 * Released stacks MUST NOT be used anymore.
 * 
 * Note: The implementation of this function does not make any assumptions
 * about the allocation method of stack elements, but MUST match the implementation
 * of function `obtain_stack` as its inverse function.
 * 
 * @param p_stack The pointer to the stack to release. The value of the pointer
 * is set to 0, if the stack was successfully released, otherwise it is left untouched.
 */
<type> stack_release(<params>);

/**
 * Determines whether or not the given stack is valid.
 * 
 * @param stack The stack to evaluate.
 * @return `True` if the stack is valid, false otherwise.
 */
<type> stack_is_valid(<params>);

/**
 * Determines whether or not the stack contains at least one item.
 * 
 * @param stack The stack to evaluate.
 * @return `False` if the stack contains one or more items, `true` otherwise.
 */
<type> stack_is_empty(<params>);

/**
 * Provides the number of values stored in the stack.
 * 
 * @param stack The stack to evaluate.
 * @return The number of values the stack contains.
 */
<type> stack_get_size(<params>);

/**
 * Clears the given stack by removing all values from the stack.
 * 
 * @param stack The stack to clear.
 */
<type> stack_clear(<params>);

/**
 * Inserts the given value to the stack.
 * 
 * @param stack The stack to which the value shall be appended.
 * @param value The value to append to the stack.
 */
<type> stack_push(<params>);

/**
 * Provides the value that 'pop' would provided but WITHOUT removing 
 * this value from the stack.
 * 
 * @param stack The stack from which the value shall be peeked.
 * @return The next value or 0, if the stack is empty.
 */
<type> stack_peek(<params>);

/**
 * Provides AND removes the top-most value from the stack.
 * 
 * @param stack The stack from which the value be removed shall be returned.
 * @return The value or 0, if the stack is empty.
 */
<type> stack_pop(<params>);

