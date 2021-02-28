/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Title:			Implementation of UTs for queues
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Tests functions of a queue.
 * ----------------------------------------------------------
 */

#include "test_queue.h"

#include <stdio.h>
#include <string.h>

#include "shortcut.h"
#include "config.h"

#include "queue.h"
#include "allocator.h"

#define ASSERT_NEW_VALID_QUEUE() _assert_new_valid_queue(tc)
IntQueue _assert_new_valid_queue(struct TestCase* tc) {
    int exp_alloc_cnt = mem_get_alloc_call_cnt() + 2;
    IntQueue queue = queue_obtain();
    ASSERT_TRUE(queue != 0, MSG("Expected non-null queue"));
    ASSERT_TRUE(queue_is_valid(queue), MSG("Expected a valid queue"));
    ASSERT_TRUE(queue_is_empty(queue), MSG("Expected an empty queue"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being called exactly once, but was called %d time(s)", mem_get_alloc_call_cnt() - exp_alloc_cnt - 1));
    ASSERT_TRUE(mem_is_allocated(queue), MSG("Expected obtained queue1 is allocated using mem_alloc"));
    return queue;
}

#define ASSERT_RESET_AND_NEW_VALID_QUEUE() _assert_reset_and_new_valid_queue(tc)
IntQueue _assert_reset_and_new_valid_queue(struct TestCase* tc) {
    mem_reset_stat();
    return _assert_new_valid_queue(tc);
}


#define ASSERT_FREE_VALID_QUEUE(p_queue) _assert_free_valid_queue(tc, p_queue)
void _assert_free_valid_queue(struct TestCase* tc, IntQueue* p_queue) {
    ASSERT_TRUE(p_queue != 0 && queue_is_valid(*p_queue), MSG("Expected a valid queue"));
    int additional_free_calls =  2 + queue_get_size(*p_queue);
    int exp_alloc_cnt = mem_get_alloc_call_cnt();
    int exp_free_cnt = mem_get_free_call_cnt() + additional_free_calls;
    ASSERT_TRUE(mem_is_allocated(*p_queue), MSG("Expected that queue to release was allocated using mem_alloc"));
    queue_release(p_queue);
    ASSERT_TRUE(p_queue != 0 && *p_queue == 0, MSG("Expected that queue was set to 0"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being NOT called, but was called %d time(s)", mem_get_alloc_call_cnt() - exp_alloc_cnt));
    ASSERT_TRUE(mem_get_free_call_cnt() == exp_free_cnt, MSG("Expected mem_free being called exactly %d time(s), but was called %d time(s)", exp_free_cnt, mem_get_free_call_cnt() - exp_free_cnt + additional_free_calls));
    ASSERT_FALSE(mem_is_allocated(*p_queue), MSG("Expected that released queue is not allocated anymore after release"));
}

#ifndef ASSERT_MEM_STATUS_EXT
#define ASSERT_MEM_STATUS_EXT(exp_alloc_call_cnt, exp_free_call_cnt, exp_block_cnt) _assert_mem_status_ext_queue(tc, exp_alloc_call_cnt, exp_free_call_cnt, exp_block_cnt)
void _assert_mem_status_ext_queue(struct TestCase* tc, int exp_alloc_call_cnt, int exp_free_call_cnt, int exp_block_cnt) {
    ASSERT_TRUE(mem_get_allocated_block_cnt() == exp_block_cnt, MSG("Expected %d allocated memory block(s), but is %d", exp_block_cnt, mem_get_allocated_block_cnt()));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_call_cnt, MSG("Expected %d mem_alloc() call(s), but is %d", exp_alloc_call_cnt, mem_get_alloc_call_cnt()));
    ASSERT_TRUE(mem_get_free_call_cnt() == exp_free_call_cnt, MSG("Expected %d mem_free() call(s), but is %d", exp_free_call_cnt, mem_get_free_call_cnt()));
}
#endif

#ifndef ASSERT_MEM_STATUS
#define ASSERT_MEM_STATUS(exp_alloc_call_cnt, exp_free_call_cnt) _assert_mem_status_ext_queue(tc, exp_alloc_call_cnt, exp_free_call_cnt, (exp_alloc_call_cnt - exp_free_call_cnt))
#endif
/* ------------------------------------------------------------------- */

TEST(test_queue_obtain__shall_allocate_a_queue_and_queue) {
    int exp_alloc_cnt = 2;
    mem_reset_stat();
    IntQueue queue = queue_obtain();
    ASSERT_TRUE(queue != 0, MSG("Expected non-null queue"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being called exactly %d time(s)", exp_alloc_cnt));
    ASSERT_TRUE(mem_is_allocated(queue), MSG("Expected obtained queue is allocated using mem_alloc"));
    if (queue != 0) {
        free(queue);
    }
}

TEST(test_queue_obtain__shall_allocate_a_fresh_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    if (queue != 0) {
        free(queue);
    }
}

TEST(test_queue_obtain__shall_allocate_a_different_queue) {
    IntQueue queue1 = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    IntQueue queue2 = ASSERT_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue1 != queue2, MSG("Expected different queues"));
    if (queue1 != 0) {
        free(queue1);
    }
    if (queue2 != 0) {
        free(queue2);
    }
}

TEST(test_queue_obtain_failed__shall_not_allocate_a_queue) {
    IntQueue queue1 = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    int exp_alloc_cnt = 1;
    mem_reset_calls();
    mem_block_allocs(true);
    IntQueue queue = queue_obtain();
    ASSERT_TRUE(queue == 0, MSG("Expected null queue"));
    ASSERT_TRUE(mem_get_alloc_call_cnt() == exp_alloc_cnt, MSG("Expected mem_alloc being called exactly %d time(s)", exp_alloc_cnt));
    if (queue != 0) {
        free(queue);
    }
    free(queue1);
}



TEST(test_queue_release__shall_release_a_valid_empty_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_FREE_VALID_QUEUE(&queue);
    ASSERT_TRUE(queue == 0, MSG("Expected that queue is set to 0"));
}

TEST(test_queue_release__shall_release_a_valid_filled_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 1);
    queue_enqueue(queue, 2);
    ASSERT_FREE_VALID_QUEUE(&queue);
    ASSERT_TRUE(queue == 0, MSG("Expected that queue is set to 0"));
}

TEST(test_queue_release__shall_ignore_release_of_an_invalid_queue) {
    IntQueue tmp = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    int block_cnt = mem_get_allocated_block_cnt();
    IntQueue* p_queue = 0;
    queue_release(p_queue);
    ASSERT_TRUE(mem_get_allocated_block_cnt() == block_cnt, MSG("Expected unchanged memory allocation"));
    ASSERT_TRUE(mem_get_free_call_cnt() == 0, MSG("Expected NO mem_free() call, but was called %d time(s)", mem_get_free_call_cnt()));

    IntQueue queue = 0;
    p_queue = &queue;
    queue_release(p_queue);
    ASSERT_TRUE(mem_get_allocated_block_cnt() == block_cnt, MSG("Expected unchanged memory allocation"));
    ASSERT_TRUE(mem_get_free_call_cnt() == 0, MSG("Expected NO mem_free() call, but was called %d time(s)", mem_get_free_call_cnt()));

    queue_release(&tmp);
}



TEST(test_queue_is_valid__shall_be_true_for_valid_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue_is_valid(queue), MSG("Expected queue to be valid"));
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_is_valid__shall_be_false_for_invalid_queue) {
    ASSERT_FALSE(queue_is_valid(0), MSG("Expected queue to be invalid"));
}



TEST(test_queue_enqueue__shall_insert_single_value_in_empty_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 31);
    ASSERT_MEM_STATUS(3, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_enqueue__shall_insert_values) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 41);
    queue_enqueue(queue, 42);
    queue_enqueue(queue, 43);
    queue_enqueue(queue, 44);
    ASSERT_MEM_STATUS(6, 0);
    ASSERT_TRUE(queue_get_size(queue) == 4, MSG("Expected queue contains 4 value"));
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_enqueue__shall_ignore_invalid_queue) {
    IntQueue tmp = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(0, 31);
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&tmp);
}



TEST(test_queue_peek__shall_get_0_from_empty_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    int val = queue_peek(queue);
    ASSERT_TRUE(val == 0, MSG("Expected value of '0' when peeking from an empty queue"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_peek__shall_get_first_added_value) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 51);
    queue_enqueue(queue, 52);
    queue_enqueue(queue, 53);
    ASSERT_MEM_STATUS(5, 0);
    int val = queue_peek(queue);
    ASSERT_TRUE(val == 51, MSG("Expected first enqueued value"));
    val = queue_peek(queue);
    ASSERT_TRUE(val == 51, MSG("Expected value was not removed from queue"));
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_peek__shall_ignore_invalid_queue) {
    IntQueue tmp = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    int val = queue_peek(0);
    ASSERT_TRUE(val == 0, MSG("Expected that no value (0) was peeked, but got %d", val));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&tmp);
}



TEST(test_queue_dequeue__shall_return_0_for_empty_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue_dequeue(queue) == 0, MSG("Expected that empty queue provides always 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_dequeue__shall_return_single_value) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 111);
    ASSERT_TRUE(queue_dequeue(queue) == 111, MSG("Expected that queue provides the value"));
    ASSERT_MEM_STATUS(3, 1);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_dequeue__shall_return_enqueued_values) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 121);
    queue_enqueue(queue, 122);
    queue_enqueue(queue, 123);
    ASSERT_TRUE(queue_dequeue(queue) == 121, MSG("Expected that queue provides the first enqueued value"));
    ASSERT_TRUE(queue_dequeue(queue) == 122, MSG("Expected that queue provides the second enqueued value"));
    ASSERT_TRUE(queue_dequeue(queue) == 123, MSG("Expected that queue provides the third enqueued value"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_dequeue__shall_return_values_in_enqueued_order) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 131);
    queue_enqueue(queue, 132);
    queue_enqueue(queue, 133);
    ASSERT_TRUE(queue_dequeue(queue) == 131, MSG("Expected that queue provides the first enqueued value"));
    queue_enqueue(queue, 134);
    ASSERT_TRUE(queue_dequeue(queue) == 132, MSG("Expected that queue provides the second enqueued value"));
    queue_enqueue(queue, 135);
    ASSERT_TRUE(queue_dequeue(queue) == 133, MSG("Expected that queue provides the third enqueued value"));
    ASSERT_TRUE(queue_dequeue(queue) == 134, MSG("Expected that queue provides the forth enqueued value"));
    ASSERT_TRUE(queue_dequeue(queue) == 135, MSG("Expected that queue provides the fifth enqueued value"));
    ASSERT_MEM_STATUS(7, 5);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_dequeue__shall_return_0_for_invalid_queue) {
    IntQueue tmp = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue_dequeue(0) == 0, MSG("Expected that invalid queue provides always 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&tmp);
}




TEST(test_queue_clear__shall_clear_empty_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_clear(queue);
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_clear__shall_clear_queue_with_one_value) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 61);
    queue_clear(queue);
    ASSERT_MEM_STATUS(3, 1);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_clear__shall_clear_queue_with_multiple_values) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 51);
    queue_enqueue(queue, 52);
    queue_enqueue(queue, 53);
    queue_clear(queue);
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_clear__shall_ingore_invalid_queue) {
    IntQueue tmp = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_clear(0);
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&tmp);
}



TEST(test_queue_is_empty__shall_be_true__for_newly_obtained_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue_is_empty(0), MSG("Expected that new queue IS empty"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_is_empty__shall_be_false__after_adding_values) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 61);
    ASSERT_FALSE(queue_is_empty(queue), MSG("Expected that queue with values IS NOT empty"));
    ASSERT_MEM_STATUS(3, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_is_empty__shall_be_true__after_clear) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 71);
    queue_enqueue(queue, 72);
    queue_enqueue(queue, 73);
    queue_clear(queue);
    ASSERT_TRUE(queue_is_empty(queue), MSG("Expected that queue IS empty after queue_clear"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_is_empty__shall_be_true_for_invalid_queue) {
    IntQueue tmp = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue_is_empty(0), MSG("Expected that invalid queue IS empty"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&tmp);
}



TEST(test_queue_get_size__shall_be_0_for_newly_obtained_queue) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue_get_size(queue) == 0, MSG("Expected that size of new queue is 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_get_size__shall_reflect_number_of_values_after_enqueueing_values) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 81);
    ASSERT_TRUE(queue_get_size(queue) == 1, MSG("Expected that size of queue is 1 after adding first value"));
    queue_enqueue(queue, 82);
    ASSERT_TRUE(queue_get_size(queue) == 2, MSG("Expected that size of queue is 2 after adding second value"));
    queue_enqueue(queue, 83);
    ASSERT_TRUE(queue_get_size(queue) == 3, MSG("Expected that size of queue is 3 after adding third value"));
    ASSERT_MEM_STATUS(5, 0);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_get_size__shall_reflect_number_of_values_after_dequeueing_values) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 91);
    queue_enqueue(queue, 92);
    queue_enqueue(queue, 93);
    ASSERT_TRUE(queue_get_size(queue) == 3, MSG("Expected that size of queue is 3 after enqueueing  values"));
    queue_dequeue(queue);
    ASSERT_TRUE(queue_get_size(queue) == 2, MSG("Expected that size of queue is 2 after dequeueing first value"));
    queue_dequeue(queue);
    ASSERT_TRUE(queue_get_size(queue) == 1, MSG("Expected that size of queue is 1 after dequeueing second value"));
    queue_dequeue(queue);
    ASSERT_TRUE(queue_get_size(queue) == 0, MSG("Expected that size of queue is 0 after dequeueing third value"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_get_size__shall_be_0_after_clear) {
    IntQueue queue = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    queue_enqueue(queue, 101);
    queue_enqueue(queue, 102);
    queue_enqueue(queue, 103);
    queue_clear(queue);
    ASSERT_TRUE(queue_get_size(queue) == 0, MSG("Expected that size of queue is 0 after clearing the queue"));
    ASSERT_MEM_STATUS(5, 3);
    ASSERT_FREE_VALID_QUEUE(&queue);
}

TEST(test_queue_get_size__shall_be_0_for_invalid_queue) {
    IntQueue tmp = ASSERT_RESET_AND_NEW_VALID_QUEUE();
    ASSERT_TRUE(queue_get_size(0) == 0, MSG("Expected that size of invalid queue is 0"));
    ASSERT_MEM_STATUS(2, 0);
    ASSERT_FREE_VALID_QUEUE(&tmp);
}