#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


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

    char *test4 = "test 4";
    char *test5 = "test 5";
    char *test6 = "test 6";

    List_push(left, test1);
    List_push(left, test2);
    List_push(left, test3);

    List_push(right, test4);
    List_push(right, test5);
    List_push(right, test6);

    List *joined = List_join(left, right);
    mu_assert(joined != NULL, "No joined list");
    mu_assert(List_count(joined) == List_count(left) + List_count(right),
            "Wrong count after join");
    mu_assert(left->first->value == joined->first->value,
            "Wrong first after join");
    mu_assert(right->last->value == joined->last->value,
            "Wrong last after join");

    List_destroy(left);
    List_destroy(right);
    List_clear_destroy(joined);

    return NULL;
}


char *test_split() {
    List *to_split = List_create();
    List_push(to_split, test1);
    List_push(to_split, test2);
    List_push(to_split, test3);

    List *left = NULL;
    List *right = NULL;

    List_split(to_split, to_split->first, &left, &right);
    mu_assert(left != NULL, "No left list");
    mu_assert(right != NULL, "No right list");
    mu_assert(List_count(left) == 1, "Wrong left count");
    mu_assert(List_count(right) == 2, "Wrong right count");
    mu_assert(left->first->value == to_split->first->value, "Wrong left first");
    mu_assert(right->first->value == to_split->first->next->value,
            "Wrong right first");
    mu_assert(left->last == left->first, "Wrong left last");
    mu_assert(right->last->value == to_split->last->value, "Wrong right last");

    List_destroy(left);
    List_destroy(right);
    List_clear_destroy(to_split);

    return NULL;
}


char *test_copy() {
    List *to_copy = List_create();
    List_push(to_copy, test1);
    List_push(to_copy, test2);
    List_push(to_copy, test3);

    List *copied = List_copy(to_copy);
    mu_assert(copied != NULL, "No copied list");
    mu_assert(copied != to_copy, "Lists are same pointer");
    mu_assert(copied->first != to_copy->first, "List nodes are same pointer");
    mu_assert(copied->first->value == to_copy->first->value,
            "List nodes have same value");

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
    mu_run_test(test_copy);

    return NULL;
}

RUN_TESTS(all_tests);
