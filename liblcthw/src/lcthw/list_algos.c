#include <assert.h>
#include <lcthw/list.h>
#include "list_algos.h"
#include "dbg.h"

int List_bubble_sort(List *list, List_compare comparator) {
    int swapped = 1;
    if (list->count < 2) return 0;

    while (swapped == 1) {
        swapped = 0;
        ListNode *start = list->first->next;
        ListNode *node = start;

        while (node != NULL) {
            ListNode *prev = node->prev;
            int rc = comparator(prev->value, node->value);
            if (rc > 0) {
                List_swap(list, prev, node);
                swapped = 1;
            }

            node = node->next;
        }
    }

    return 0;
}

List *List_merge(List *left, List *right, List_compare comparator) {
    assert(left != NULL);
    assert(right != NULL);
    List *result = List_create();
    while (left->count > 0 || right->count > 0) {
        if (left->count > 0 && right->count > 0) {
            if (comparator(left->first->value, right->first->value) <= 0) {
                List_push(result, List_shift(left));
            } else {
                List_push(result, List_shift(right));
            }
        } else if (left->count > 0) {
            List_join(result, left);
            left->count = 0;
        } else if (right->count > 0) {
            List_join(result, right);
            right->count = 0;
        }
    }

    free(left);
    free(right);
    return result;
}

List *List_merge_sort(List *list, List_compare comparator) {
    assert(list != NULL);
    if (list->count <= 1) return List_copy(list);
    List *left = List_copy(list);
    List *right = NULL;

    ListNode *slow = left->first;
    int i = 0;
    for (i = 0; i < (left->count - 1) / 2 && slow != NULL; i++) {
        slow = slow->next;
    }

    List_split(left, slow, &right, 1);
    left = List_merge_sort(left, comparator);
    right = List_merge_sort(right, comparator);

    return List_merge(left, right, comparator);
}
