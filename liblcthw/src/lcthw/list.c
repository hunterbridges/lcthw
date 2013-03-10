#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <assert.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    assert(list != NULL);
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}


void List_clear(List *list)
{
    assert(list != NULL);
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void List_clear_destroy(List *list)
{
    assert(list != NULL);
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
        free(cur->value);
    }

    free(list->last);
    free(list);
}


void List_push(List *list, void *value)
{
    assert(list != NULL);
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    assert(list != NULL);
    assert(list->count > 0);
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    assert(list != NULL);
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    assert(list != NULL);
    assert(list->count > 0);
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    assert(list != NULL);
    assert(list->count > 0);
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

void List_join(List *left, List *right) {
    assert(left != NULL);
    assert(right != NULL);

    ListNode *l_last = left->last;
    ListNode *r_first = right->first;
    ListNode *r_last = right->last;

    if (l_last) l_last->next = r_first;
    if (r_first) r_first->prev = l_last;
    left->last = r_last ? r_last : l_last;
    left->count += right->count;

    right->first = NULL;
    right->last = NULL;
    right->count = 0;
}

void List_split(List *list, ListNode *splitter, List **remainder, int recount) {
    assert(list != NULL);
    assert(splitter != NULL);

    *remainder = NULL;
    if (splitter->next == NULL) return;
    ListNode *prev_last = list->last;
    list->last = splitter;

    *remainder = List_create();
    (*remainder)->first = splitter->next;
    (*remainder)->last = prev_last;

    if ((*remainder)->first) (*remainder)->first->prev = NULL;
    splitter->next = NULL;

    if (recount == 0) return;
    int count = 0;
    for (ListNode *node = (*remainder)->first; node != NULL;
            node = node->next) {
        count++;
    }
    (*remainder)->count = count;
    list->count -= count;
}

void ListNode_swap(ListNode *a, ListNode *b) {
    assert(a != NULL);
    assert(b != NULL);

    void *tmp = a->value;
    a->value = b->value;
    b->value = tmp;
}

List *List_copy(List *list) {
    assert(list != NULL);

    List *copied = List_create();
    int i = 0;
    LIST_FOREACH(list, first, next, cur) {
        List_push(copied, cur->value);
        i++;
    }

    return copied;
}
