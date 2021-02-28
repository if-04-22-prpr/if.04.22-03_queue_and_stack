/*----------------------------------------------------------
 *				HTBLA-Leonding
 * ---------------------------------------------------------
 * Title:			Tests implementation of a Liked List.
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Unit tests for a linked list implemenation.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

#include "shortcut.h"
#include "test_list.h"
#include "test_queue.h"
#include "test_stack.h"

int main(int argc, char *argv[])
{
	/* ================================= */
	/*   LIST */

	ADD_TEST(test_list_obtain__shall_allocate_a_list);
	ADD_TEST(test_list_obtain__shall_allocate_a_fresh_list);
	ADD_TEST(test_list_obtain__shall_allocate_a_different_list);
	ADD_TEST(test_list_obtain_failed__shall_not_allocate_a_list);

	ADD_TEST(test_list_release__shall_release_a_valid_empty_list);
	ADD_TEST(test_list_release__shall_release_a_valid_filled_list);
	ADD_TEST(test_list_release__shall_ignore_release_of_an_invalid_list);
	
	ADD_TEST(test_list_is_valid__shall_be_true_for_valid_list);
	ADD_TEST(test_list_is_valid__shall_be_false_for_invalid_list);
	
	ADD_TEST(test_list_insert__shall_add_one_value_to_empty_list);
	ADD_TEST(test_list_insert__shall_add_multiple_values);
	ADD_TEST(test_list_insert__shall_ignore_invalid_list);
	
	/* NOT USED in this assignment 
	ADD_TEST(test_list_remove__shall_not_remove_from_empty_list);
	ADD_TEST(test_list_remove__shall_remove_only_value);
	ADD_TEST(test_list_remove__shall_remove_one_value);
	ADD_TEST(test_list_remove__shall_remove_first_value);
	ADD_TEST(test_list_remove__shall_remove_value_in_the_middle);
	ADD_TEST(test_list_remove__shall_remove_value_at_the_end);
	ADD_TEST(test_list_remove__shall_not_remove_missing_value);
	*/
	
	/* NOT USED in this assignment 
	ADD_TEST(test_list_remove_all__shall_not_remove_from_empty_list);
	ADD_TEST(test_list_remove_all__shall_remove_only_value);
	ADD_TEST(test_list_remove_all__shall_remove_all_values);
	ADD_TEST(test_list_remove_all__shall_remove_one_value);
	ADD_TEST(test_list_remove_all__shall_remove_all_values_in_a_row);
	ADD_TEST(test_list_remove_all__shall_remove_all_distributed_values);
	ADD_TEST(test_list_remove_all__shall_not_remove_missing_value);
	ADD_TEST(test_list_remove_all__shall_ignore_invalid_list);
	*/
	
	ADD_TEST(test_list_insert_at__shall_insert_single_value_in_empty_list);
	ADD_TEST(test_list_insert_at__shall_insert_value_at_the_beginning);
	ADD_TEST(test_list_insert_at__shall_insert_value_in_the_middle);
	ADD_TEST(test_list_insert_at__shall_insert_value_at_the_end);
	ADD_TEST(test_list_insert_at__shall_insert_value_after_the_end);
	ADD_TEST(test_list_insert_at__shall_ignore_invalid_list);
	
	ADD_TEST(test_list_remove_at__shall_not_remove_from_empty_list);
	ADD_TEST(test_list_remove_at__shall_remove_value_at_the_beginning);
	ADD_TEST(test_list_remove_at__shall_remove_value_in_the_middle);
	ADD_TEST(test_list_remove_at__shall_not_remove_from_empty_list);
	ADD_TEST(test_list_remove_at__shall_remove_value_at_the_end);
	ADD_TEST(test_list_remove_at__shall_not_remove_value_after_the_end);
	ADD_TEST(test_list_remove_at__shall_ignore_invalid_list);
	
	ADD_TEST(test_list_clear__shall_clear_empty_list);
	ADD_TEST(test_list_clear__shall_clear_list_with_one_value);
	ADD_TEST(test_list_clear__shall_clear_list_with_multiple_values);
	ADD_TEST(test_list_clear__shall_ingore_invalid_list);
	
	ADD_TEST(test_list_is_empty__shall_be_true__for_newly_obtained_list);
	ADD_TEST(test_list_is_empty__shall_be_false__after_adding_values);
	ADD_TEST(test_list_is_empty__shall_be_true__after_clear);
	ADD_TEST(test_list_is_empty__shall_be_true_for_invalid_list);
	
	ADD_TEST(test_list_get_size__shall_be_0_for_newly_obtained_list);
	ADD_TEST(test_list_get_size__shall_reflect_number_of_values_after_adding_values);
	ADD_TEST(test_list_get_size__shall_reflect_number_of_values_after_removing_values);
	ADD_TEST(test_list_get_size__shall_be_0_after_clear);
	ADD_TEST(test_list_get_size__shall_be_0_for_invalid_list);
	
	/* NOT USED in this assignment 
	ADD_TEST(test_list_contains__shall_be_false_for_empty_list);
	ADD_TEST(test_list_contains__shall_be_true_for_one_value);
	ADD_TEST(test_list_contains__shall_be_true_for_multiple_values);
	ADD_TEST(test_list_contains__shall_be_false_form_missing_value);
	ADD_TEST(test_list_contains__shall_be_false_for_invalid_list);
	*/
	
	ADD_TEST(test_list_get_at__shall_return_0_for_empty_list);
	ADD_TEST(test_list_get_at__shall_return_single_value);
	ADD_TEST(test_list_get_at__shall_return_first_value);
	ADD_TEST(test_list_get_at__shall_return_values_in_added_order);
	ADD_TEST(test_list_get_at__shall_return_0_for_invalid_list);
	
	/* NOT USED in this assignment 
	ADD_TEST(test_list_append__shall_append_empty_list_to_empty_list);
	ADD_TEST(test_list_append__shall_append_filled_list_to_empty_list);
	ADD_TEST(test_list_append__shall_append_empty_list_to_filled_list);
	ADD_TEST(test_list_append__shall_append_filled_list_to_filled_list);
	ADD_TEST(test_list_append__shall_ignore_invalid_lists);
	*/

	/* ================================= */
	/*   QUEUE */

	ADD_TEST(test_queue_obtain__shall_allocate_a_queue_and_queue);
	ADD_TEST(test_queue_obtain__shall_allocate_a_fresh_queue);
	ADD_TEST(test_queue_obtain__shall_allocate_a_different_queue);
	ADD_TEST(test_queue_obtain_failed__shall_not_allocate_a_queue);

	ADD_TEST(test_queue_release__shall_release_a_valid_empty_queue);
	ADD_TEST(test_queue_release__shall_release_a_valid_filled_queue);
	ADD_TEST(test_queue_release__shall_ignore_release_of_an_invalid_queue);

	ADD_TEST(test_queue_is_valid__shall_be_true_for_valid_queue);
	ADD_TEST(test_queue_is_valid__shall_be_false_for_invalid_queue);

	ADD_TEST(test_queue_enqueue__shall_insert_single_value_in_empty_queue);
	ADD_TEST(test_queue_enqueue__shall_insert_values);
	ADD_TEST(test_queue_enqueue__shall_ignore_invalid_queue);

	ADD_TEST(test_queue_peek__shall_get_0_from_empty_queue);
	ADD_TEST(test_queue_peek__shall_get_first_added_value);
	ADD_TEST(test_queue_peek__shall_ignore_invalid_queue);

	ADD_TEST(test_queue_dequeue__shall_return_0_for_empty_queue);
	ADD_TEST(test_queue_dequeue__shall_return_single_value);
	ADD_TEST(test_queue_dequeue__shall_return_enqueued_values);
	ADD_TEST(test_queue_dequeue__shall_return_values_in_enqueued_order);
	ADD_TEST(test_queue_dequeue__shall_return_0_for_invalid_queue);

	ADD_TEST(test_queue_is_empty__shall_be_true__for_newly_obtained_queue);
	ADD_TEST(test_queue_is_empty__shall_be_false__after_adding_values);
	ADD_TEST(test_queue_is_empty__shall_be_true__after_clear);
	ADD_TEST(test_queue_is_empty__shall_be_true_for_invalid_queue);

	ADD_TEST(test_queue_get_size__shall_be_0_for_newly_obtained_queue);
	ADD_TEST(test_queue_get_size__shall_reflect_number_of_values_after_enqueueing_values);
	ADD_TEST(test_queue_get_size__shall_reflect_number_of_values_after_dequeueing_values);
	ADD_TEST(test_queue_get_size__shall_be_0_after_clear);
	ADD_TEST(test_queue_get_size__shall_be_0_for_invalid_queue);


	/* ================================= */
	/*   STACK */

	ADD_TEST(test_stack_obtain__shall_allocate_a_stack_and_stack);
	ADD_TEST(test_stack_obtain__shall_allocate_a_fresh_stack);
	ADD_TEST(test_stack_obtain__shall_allocate_a_different_stack);
	ADD_TEST(test_stack_obtain_failed__shall_not_allocate_a_stack);

	ADD_TEST(test_stack_release__shall_release_a_valid_empty_stack);
	ADD_TEST(test_stack_release__shall_release_a_valid_filled_stack);
	ADD_TEST(test_stack_release__shall_ignore_release_of_an_invalid_stack);

	ADD_TEST(test_stack_is_valid__shall_be_true_for_valid_stack);
	ADD_TEST(test_stack_is_valid__shall_be_false_for_invalid_stack);

	ADD_TEST(test_stack_push__shall_insert_single_value_in_empty_stack);
	ADD_TEST(test_stack_push__shall_insert_values);
	ADD_TEST(test_stack_push__shall_ignore_invalid_stack);

	ADD_TEST(test_stack_peek__shall_get_0_from_empty_stack);
	ADD_TEST(test_stack_peek__shall_get_last_added_value);
	ADD_TEST(test_stack_peek__shall_ignore_invalid_stack);

	ADD_TEST(test_stack_pop__shall_return_0_for_empty_stack);
	ADD_TEST(test_stack_pop__shall_return_single_value);
	ADD_TEST(test_stack_pop__shall_return_pushed_values);
	ADD_TEST(test_stack_pop__shall_return_values_in_pushed_order);
	ADD_TEST(test_stack_pop__shall_return_0_for_invalid_stack);

	ADD_TEST(test_stack_is_empty__shall_be_true__for_newly_obtained_stack);
	ADD_TEST(test_stack_is_empty__shall_be_false__after_adding_values);
	ADD_TEST(test_stack_is_empty__shall_be_true__after_clear);
	ADD_TEST(test_stack_is_empty__shall_be_true_for_invalid_stack);

	ADD_TEST(test_stack_get_size__shall_be_0_for_newly_obtained_stack);
	ADD_TEST(test_stack_get_size__shall_reflect_number_of_values_after_pushing_values);
	ADD_TEST(test_stack_get_size__shall_reflect_number_of_values_after_poping_values);
	ADD_TEST(test_stack_get_size__shall_be_0_after_clear);
	ADD_TEST(test_stack_get_size__shall_be_0_for_invalid_stack);

	run_tests();
	return 0;
}
