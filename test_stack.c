/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Title:			Implementation of UTs for stacks
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Tests functions of a stack.
 * ----------------------------------------------------------
 */

#include "test_stack.h"

#include <stdio.h>
#include <string.h>

#include "shortcut.h"
#include "config.h"

#include "stack.h"
#include "allocator.h"

#define ASSERT_NEW_VALID_STACK() _assert_new_valid_stack(tc)
IntStack _assert_new_valid_stack(struct TestCase* tc) {
    int exp_alloc_cnt = mem_get_alloc_call_cnt() + 2;
    IntStack stack = stack_obtain();
    ASSERT_TRUE(stack != 0, MSG("Expected non-null stack"));
    ASSERT_TRUE(stack_is_valid(stack), MSG("Expected a valid stack"));
    ASSERT_TRUE(stack_is_empty(stack), MSG("Expected an empty stack"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being called exactly once, but was called %d time(s)", mem_get_alloc_call_cnt() - exp_alloc_cnt - 1));
    ASSERT_TRUE(mem_is_allocated(stack), MSG("Expected obtained stack1 is allocated using mem_alloc"));
    return stack;
}

#define ASSERT_RESET_AND_NEW_VALID_STACK() _assert_reset_and_new_valid_stack(tc)
IntStack _assert_reset_and_new_valid_stack(struct TestCase* tc) {
    mem_reset_stat();
    return _assert_new_valid_stack(tc);
}


#define ASSERT_FREE_VALID_STACK(p_stack) _assert_free_valid_stack(tc, p_stack)
void _assert_free_valid_stack(struct TestCase* tc, IntStack* p_stack) {
    ASSERT_TRUE(p_stack != 0 && stack_is_valid(*p_stack), MSG("Expected a valid stack"));
    int additional_free_calls =  2 + stack_get_size(*p_stack);
    int exp_alloc_cnt = mem_get_alloc_call_cnt();
    int exp_free_cnt = mem_get_free_call_cnt() + additional_free_calls;
    ASSERT_TRUE(mem_is_allocated(*p_stack), MSG("Expected that stack to release was allocated using mem_alloc"));
    stack_release(p_stack);
    ASSERT_TRUE(p_stack != 0 && *p_stack == 0, MSG("Expected that stack was set to 0"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being NOT called, but was called %d time(s)", mem_get_alloc_call_cnt() - exp_alloc_cnt));
    ASSERT_TRUE(mem_get_free_call_cnt() == exp_free_cnt, MSG("Expected mem_free being called exactly %d time(s), but was called %d time(s)", exp_free_cnt, mem_get_free_call_cnt() - exp_free_cnt + additional_free_calls));
    ASSERT_FALSE(mem_is_allocated(*p_stack), MSG("Expected that released stack is not allocated anymore after release"));
}

#ifndef ASSERT_MEM_STATUS_EXT
#define ASSERT_MEM_STATUS_EXT(exp_alloc_call_cnt, exp_free_call_cnt, exp_block_cnt) _assert_mem_status_ext_stack(tc, exp_alloc_call_cnt, exp_free_call_cnt, exp_block_cnt)
void _assert_mem_status_ext_stack(struct TestCase* tc, int exp_alloc_call_cnt, int exp_free_call_cnt, int exp_block_cnt) {
    ASSERT_TRUE(mem_get_allocated_block_cnt() == exp_block_cnt, MSG("Expected %d allocated memory block(s), but is %d", exp_block_cnt, mem_get_allocated_block_cnt()));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_call_cnt, MSG("Expected %d mem_alloc() call(s), but is %d", exp_alloc_call_cnt, mem_get_alloc_call_cnt()));
    ASSERT_TRUE(mem_get_free_call_cnt() == exp_free_call_cnt, MSG("Expected %d mem_free() call(s), but is %d", exp_free_call_cnt, mem_get_free_call_cnt()));
}
#endif

#ifndef ASSERT_MEM_STATUS
#define ASSERT_MEM_STATUS(exp_alloc_call_cnt, exp_free_call_cnt) _assert_mem_status_ext_stack(tc, exp_alloc_call_cnt, exp_free_call_cnt, (exp_alloc_call_cnt - exp_free_call_cnt))
#endif

/* ------------------------------------------------------------------- */

TEST(test_stack_obtain__shall_allocate_a_stack_and_stack) {
    int exp_alloc_cnt = 2;
    mem_reset_stat();
    IntStack stack = stack_obtain();
    ASSERT_TRUE(stack != 0, MSG("Expected non-null stack"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being called exactly %d time(s)", exp_alloc_cnt));
    ASSERT_TRUE(mem_is_allocated(stack), MSG("Expected obtained stack is allocated using mem_alloc"));
    if (stack != 0) {
        free(stack);
    }
}

TEST(test_stack_obtain__shall_allocate_a_fresh_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    if (stack != 0) {
        free(stack);
    }
}

TEST(test_stack_obtain__shall_allocate_a_different_stack) {
    IntStack stack1 = ASSERT_RESET_AND_NEW_VALID_STACK();
    IntStack stack2 = ASSERT_NEW_VALID_STACK();
    ASSERT_TRUE(stack1 != stack2, MSG("Expected different stacks"));
    if (stack1 != 0) {
        free(stack1);
    }
    if (stack2 != 0) {
        free(stack2);
    }
}

TEST(test_stack_obtain_failed__shall_not_allocate_a_stack) {
    IntStack stack1 = ASSERT_RESET_AND_NEW_VALID_STACK();
    int exp_alloc_cnt = 1;
    mem_reset_calls();
    mem_block_allocs(true);
    IntStack stack = stack_obtain();
    ASSERT_TRUE(stack == 0, MSG("Expected null stack"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being called exactly %d time(s)", exp_alloc_cnt));
    if (stack != 0) {
        free(stack);
    }
    free(stack1);
}



TEST(test_stack_release__shall_release_a_valid_empty_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_FREE_VALID_STACK(&stack);
    ASSERT_TRUE(stack == 0, MSG("Expected that stack is set to 0"));
}

TEST(test_stack_release__shall_release_a_valid_filled_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 1);
    stack_push(stack, 2);
    ASSERT_FREE_VALID_STACK(&stack);
    ASSERT_TRUE(stack == 0, MSG("Expected that stack is set to 0"));
}

TEST(test_stack_release__shall_ignore_release_of_an_invalid_stack) {
    IntStack tmp = ASSERT_RESET_AND_NEW_VALID_STACK();
    int block_cnt = mem_get_allocated_block_cnt();
    IntStack* p_stack = 0;
    stack_release(p_stack);
    ASSERT_TRUE(mem_get_allocated_block_cnt() == block_cnt, MSG("Expected unchanged memory allocation"));
    ASSERT_TRUE(mem_get_free_call_cnt() == 0, MSG("Expected NO mem_free() call, but was called %d time(s)", mem_get_free_call_cnt()));

    IntStack stack = 0;
    p_stack = &stack;
    stack_release(p_stack);
    ASSERT_TRUE(mem_get_allocated_block_cnt() == block_cnt, MSG("Expected unchanged memory allocation"));
    ASSERT_TRUE(mem_get_free_call_cnt() == 0, MSG("Expected NO mem_free() call, but was called %d time(s)", mem_get_free_call_cnt()));

    stack_release(&tmp);
}



TEST(test_stack_is_valid__shall_be_true_for_valid_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_TRUE(stack_is_valid(stack), MSG("Expected stack to be valid"));
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_is_valid__shall_be_false_for_invalid_stack) {
    ASSERT_FALSE(stack_is_valid(0), MSG("Expected stack to be invalid"));
}



TEST(test_stack_push__shall_insert_single_value_in_empty_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 31);
    ASSERT_MEM_STATUS(3, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_push__shall_insert_values) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 41);
    stack_push(stack, 42);
    stack_push(stack, 43);
    stack_push(stack, 44);
    ASSERT_MEM_STATUS(6, 0);
    ASSERT_TRUE(stack_get_size(stack) == 4, MSG("Expected stack contains 4 value"));
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_push__shall_ignore_invalid_stack) {
    IntStack tmp = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(0, 31);
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&tmp);
}



TEST(test_stack_peek__shall_get_0_from_empty_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    int val = stack_peek(stack);
    ASSERT_TRUE(val == 0, MSG("Expected value of '0' when peeking from an empty stack"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_peek__shall_get_last_added_value) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 51);
    stack_push(stack, 52);
    stack_push(stack, 53);
    ASSERT_MEM_STATUS(5, 0);
    int val = stack_peek(stack);
    ASSERT_TRUE(val == 53, MSG("Expected last pushed value"));
    val = stack_peek(stack);
    ASSERT_TRUE(val == 53, MSG("Expected value was not removed from stack"));
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_peek__shall_ignore_invalid_stack) {
    IntStack tmp = ASSERT_RESET_AND_NEW_VALID_STACK();
    int val = stack_peek(0);
    ASSERT_TRUE(val == 0, MSG("Expected that no value (0) was peeked, but got %d", val));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&tmp);
}



TEST(test_stack_pop__shall_return_0_for_empty_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_TRUE(stack_pop(stack) == 0, MSG("Expected that empty stack provides always 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_pop__shall_return_single_value) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 111);
    ASSERT_TRUE(stack_pop(stack) == 111, MSG("Expected that stack provides the value"));
    ASSERT_MEM_STATUS(3, 1);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_pop__shall_return_pushed_values) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 121);
    stack_push(stack, 122);
    stack_push(stack, 123);
    ASSERT_TRUE(stack_pop(stack) == 123, MSG("Expected that stack provides the third pushed value"));
    ASSERT_TRUE(stack_pop(stack) == 122, MSG("Expected that stack provides the second pushed value"));
    ASSERT_TRUE(stack_pop(stack) == 121, MSG("Expected that stack provides the first pushed value"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_pop__shall_return_values_in_pushed_order) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 131);
    stack_push(stack, 132);
    stack_push(stack, 133);
    ASSERT_TRUE(stack_pop(stack) == 133, MSG("Expected that stack provides the third pushed value"));
    stack_push(stack, 134);
    ASSERT_TRUE(stack_pop(stack) == 134, MSG("Expected that stack provides the forth pushed value"));
    stack_push(stack, 135);
    ASSERT_TRUE(stack_pop(stack) == 135, MSG("Expected that stack provides the fifth pushed value"));
    ASSERT_TRUE(stack_pop(stack) == 132, MSG("Expected that stack provides the second pushed value"));
    ASSERT_TRUE(stack_pop(stack) == 131, MSG("Expected that stack provides the first pushed value"));
    ASSERT_MEM_STATUS(7, 5);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_pop__shall_return_0_for_invalid_stack) {
    IntStack tmp = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_TRUE(stack_pop(0) == 0, MSG("Expected that invalid stack provides always 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&tmp);
}




TEST(test_stack_clear__shall_clear_empty_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_clear(stack);
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_clear__shall_clear_stack_with_one_value) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 61);
    stack_clear(stack);
    ASSERT_MEM_STATUS(3, 1);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_clear__shall_clear_stack_with_multiple_values) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 51);
    stack_push(stack, 52);
    stack_push(stack, 53);
    stack_clear(stack);
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_clear__shall_ingore_invalid_stack) {
    IntStack tmp = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_clear(0);
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&tmp);
}



TEST(test_stack_is_empty__shall_be_true__for_newly_obtained_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_TRUE(stack_is_empty(0), MSG("Expected that new stack IS empty"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_is_empty__shall_be_false__after_adding_values) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 61);
    ASSERT_FALSE(stack_is_empty(stack), MSG("Expected that stack with values IS NOT empty"));
    ASSERT_MEM_STATUS(3, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_is_empty__shall_be_true__after_clear) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 71);
    stack_push(stack, 72);
    stack_push(stack, 73);
    stack_clear(stack);
    ASSERT_TRUE(stack_is_empty(stack), MSG("Expected that stack IS empty after stack_clear"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_is_empty__shall_be_true_for_invalid_stack) {
    IntStack tmp = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_TRUE(stack_is_empty(0), MSG("Expected that invalid stack IS empty"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&tmp);
}



TEST(test_stack_get_size__shall_be_0_for_newly_obtained_stack) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_TRUE(stack_get_size(stack) == 0, MSG("Expected that size of new stack is 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_get_size__shall_reflect_number_of_values_after_pushing_values) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 81);
    ASSERT_TRUE(stack_get_size(stack) == 1, MSG("Expected that size of stack is 1 after adding first value"));
    stack_push(stack, 82);
    ASSERT_TRUE(stack_get_size(stack) == 2, MSG("Expected that size of stack is 2 after adding second value"));
    stack_push(stack, 83);
    ASSERT_TRUE(stack_get_size(stack) == 3, MSG("Expected that size of stack is 3 after adding third value"));
    ASSERT_MEM_STATUS(5, 0);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_get_size__shall_reflect_number_of_values_after_poping_values) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 91);
    stack_push(stack, 92);
    stack_push(stack, 93);
    ASSERT_TRUE(stack_get_size(stack) == 3, MSG("Expected that size of stack is 3 after pushing  values"));
    stack_pop(stack);
    ASSERT_TRUE(stack_get_size(stack) == 2, MSG("Expected that size of stack is 2 after poping first value"));
    stack_pop(stack);
    ASSERT_TRUE(stack_get_size(stack) == 1, MSG("Expected that size of stack is 1 after poping second value"));
    stack_pop(stack);
    ASSERT_TRUE(stack_get_size(stack) == 0, MSG("Expected that size of stack is 0 after poping third value"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_get_size__shall_be_0_after_clear) {
    IntStack stack = ASSERT_RESET_AND_NEW_VALID_STACK();
    stack_push(stack, 101);
    stack_push(stack, 102);
    stack_push(stack, 103);
    stack_clear(stack);
    ASSERT_TRUE(stack_get_size(stack) == 0, MSG("Expected that size of stack is 0 after clearing the stack"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_STACK(&stack);
}

TEST(test_stack_get_size__shall_be_0_for_invalid_stack) {
    IntStack tmp = ASSERT_RESET_AND_NEW_VALID_STACK();
    ASSERT_TRUE(stack_get_size(0) == 0, MSG("Expected that size of invalid stack is 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_STACK(&tmp);
}