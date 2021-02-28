/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Title:			Unit Tests for a Queue implementation
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Tests functions of a queue.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_QUEUE_H
#define ___TEST_QUEUE_H

#include "shortcut.h"

TEST(test_queue_obtain__shall_allocate_a_queue_and_queue);
TEST(test_queue_obtain__shall_allocate_a_fresh_queue);
TEST(test_queue_obtain__shall_allocate_a_different_queue);
TEST(test_queue_obtain_failed__shall_not_allocate_a_queue);

TEST(test_queue_release__shall_release_a_valid_empty_queue);
TEST(test_queue_release__shall_release_a_valid_filled_queue);
TEST(test_queue_release__shall_ignore_release_of_an_invalid_queue);

TEST(test_queue_is_valid__shall_be_true_for_valid_queue);
TEST(test_queue_is_valid__shall_be_false_for_invalid_queue);

TEST(test_queue_enqueue__shall_insert_single_value_in_empty_queue);
TEST(test_queue_enqueue__shall_insert_values);
TEST(test_queue_enqueue__shall_ignore_invalid_queue);

TEST(test_queue_peek__shall_get_0_from_empty_queue);
TEST(test_queue_peek__shall_get_first_added_value);
TEST(test_queue_peek__shall_ignore_invalid_queue);

TEST(test_queue_dequeue__shall_return_0_for_empty_queue);
TEST(test_queue_dequeue__shall_return_single_value);
TEST(test_queue_dequeue__shall_return_enqueued_values);
TEST(test_queue_dequeue__shall_return_values_in_enqueued_order);
TEST(test_queue_dequeue__shall_return_0_for_invalid_queue);

TEST(test_queue_is_empty__shall_be_true__for_newly_obtained_queue);
TEST(test_queue_is_empty__shall_be_false__after_adding_values);
TEST(test_queue_is_empty__shall_be_true__after_clear);
TEST(test_queue_is_empty__shall_be_true_for_invalid_queue);

TEST(test_queue_get_size__shall_be_0_for_newly_obtained_queue);
TEST(test_queue_get_size__shall_reflect_number_of_values_after_enqueueing_values);
TEST(test_queue_get_size__shall_reflect_number_of_values_after_dequeueing_values);
TEST(test_queue_get_size__shall_be_0_after_clear);
TEST(test_queue_get_size__shall_be_0_for_invalid_queue);

#endif
