/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Title:			Unit Tests for a Stack implementation
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Tests functions of a stack.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_STACK_H
#define ___TEST_STACK_H

#include "shortcut.h"

TEST(test_stack_obtain__shall_allocate_a_stack_and_stack);
TEST(test_stack_obtain__shall_allocate_a_fresh_stack);
TEST(test_stack_obtain__shall_allocate_a_different_stack);
TEST(test_stack_obtain_failed__shall_not_allocate_a_stack);

TEST(test_stack_release__shall_release_a_valid_empty_stack);
TEST(test_stack_release__shall_release_a_valid_filled_stack);
TEST(test_stack_release__shall_ignore_release_of_an_invalid_stack);

TEST(test_stack_is_valid__shall_be_true_for_valid_stack);
TEST(test_stack_is_valid__shall_be_false_for_invalid_stack);

TEST(test_stack_push__shall_insert_single_value_in_empty_stack);
TEST(test_stack_push__shall_insert_values);
TEST(test_stack_push__shall_ignore_invalid_stack);

TEST(test_stack_peek__shall_get_0_from_empty_stack);
TEST(test_stack_peek__shall_get_last_added_value);
TEST(test_stack_peek__shall_ignore_invalid_stack);

TEST(test_stack_pop__shall_return_0_for_empty_stack);
TEST(test_stack_pop__shall_return_single_value);
TEST(test_stack_pop__shall_return_pushed_values);
TEST(test_stack_pop__shall_return_values_in_pushed_order);
TEST(test_stack_pop__shall_return_0_for_invalid_stack);

TEST(test_stack_is_empty__shall_be_true__for_newly_obtained_stack);
TEST(test_stack_is_empty__shall_be_false__after_adding_values);
TEST(test_stack_is_empty__shall_be_true__after_clear);
TEST(test_stack_is_empty__shall_be_true_for_invalid_stack);

TEST(test_stack_get_size__shall_be_0_for_newly_obtained_stack);
TEST(test_stack_get_size__shall_reflect_number_of_values_after_pushing_values);
TEST(test_stack_get_size__shall_reflect_number_of_values_after_poping_values);
TEST(test_stack_get_size__shall_be_0_after_clear);
TEST(test_stack_get_size__shall_be_0_for_invalid_stack);

#endif
