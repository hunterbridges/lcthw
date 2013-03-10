#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


int count_valid(List *list) {
    assert(list != NULL);
    int actual = 0;
    LIST_FOREACH(list, first, next, cur) {
        actual++;
    }
    int rc = (actual == list->count);
    if (rc == 0) debug("List: %d, Actual: %d", list->count, actual);
    return rc;
}


char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}


char *test_destroy ()
{
    List_clear_destroy(list);

    return NULL;
}


char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}


char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}


char *test_join() {
    List *left = List_create();
    List *right = List_create();

    char *test4 = calloc(7, sizeof(char));
    stpcpy(test4, "test 4");
    char *test5 = calloc(7, sizeof(char));
    stpcpy(test5, "test 5");
    char *test6 = calloc(7, sizeof(char));
    stpcpy(test6, "test 6");
    char *test7 = calloc(7, sizeof(char));
    stpcpy(test7, "test 7");
    char *test8 = calloc(7, sizeof(char));
    stpcpy(test8, "test 8");
    char *test9 = calloc(7, sizeof(char));
    stpcpy(test9, "test 9");

    List_push(left, test4);
    List_push(left, test5);
    List_push(left, test6);

    List_push(right, test7);
    List_push(right, test8);
    List_push(right, test9);

    int check_count = List_count(left) + List_count(right);
    ListNode *check_first = left->first;
    ListNode *check_last = right->last;

    List_join(left, right);
    free(right);
    right = NULL;

    mu_assert(left != NULL, "No left list");
    mu_assert(List_count(left) == check_count,
            "Wrong count after join");
    mu_assert(left->first == check_first,
            "Wrong first after join");
    mu_assert(left->last == check_last,
            "Wrong last after join");
    List_clear_destroy(left);

    return NULL;
}


char *test_split() {
    List *to_split = List_create();

    char *test4 = calloc(7, sizeof(char));
    stpcpy(test4, "test 4");
    char *test5 = calloc(7, sizeof(char));
    stpcpy(test5, "test 5");
    char *test6 = calloc(7, sizeof(char));
    stpcpy(test6, "test 6");
    List_push(to_split, test4);
    List_push(to_split, test5);
    List_push(to_split, test6);

    List *right = NULL;
    ListNode *right_first = to_split->first->next;
    ListNode *right_last = to_split->last;

    List_split(to_split, to_split->first, &right, 1);
    mu_assert(right != NULL, "No right list");
    mu_assert(List_count(to_split) == 1, "Wrong left count");
    mu_assert(List_count(right) == 2, "Wrong right count");
    mu_assert(count_valid(to_split), "Left count invalid");
    mu_assert(count_valid(right), "Right count invalid");
    mu_assert(to_split->last == to_split->first, "Wrong left last");
    mu_assert(right->first == right_first, "Wrong right first");
    mu_assert(right->last == right_last, "Wrong right last");

    List_clear_destroy(to_split);
    List_clear_destroy(right);

    return NULL;
}


char *test_swap() {
    List *to_swap = List_create();
    char *test_a = "test a";
    char *test_b = "test b";
    List_push(to_swap, test_a);
    List_push(to_swap, test_b);
    List_swap(to_swap, to_swap->first, to_swap->last);
    mu_assert(to_swap->first->value == "test b", "Wrong list first");
    mu_assert(to_swap->last->value == "test a", "Wrong list last");
    mu_assert(to_swap->first->next->value == "test a", "Wrong list first next");
    mu_assert(to_swap->last->prev->value == "test b", "Wrong list last prev");

    return NULL;
}


char *test_copy() {
    List *to_copy = List_create();
    char *test4 = calloc(7, sizeof(char));
    stpcpy(test4, "test 4");
    char *test5 = calloc(7, sizeof(char));
    stpcpy(test5, "test 5");
    char *test6 = calloc(7, sizeof(char));
    stpcpy(test6, "test 6");
    List_push(to_copy, test4);
    List_push(to_copy, test5);
    List_push(to_copy, test6);

    List *copied = List_copy(to_copy);
    mu_assert(copied != NULL, "No copied list");
    mu_assert(copied != to_copy, "Lists are same pointer");
    mu_assert(copied->first != to_copy->first, "List nodes are same pointer");
    mu_assert(copied->first->value == to_copy->first->value,
            "List nodes have same value");
    mu_assert(count_valid(copied), "List count invalid");

    List_destroy(to_copy);
    List_clear_destroy(copied);

    return NULL;
}


char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);
    mu_run_test(test_join);
    mu_run_test(test_split);
    mu_run_test(test_swap);
    mu_run_test(test_copy);

    return NULL;
}

RUN_TESTS(all_tests);
