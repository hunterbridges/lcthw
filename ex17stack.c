#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Stack {
    int length;
    void *members[SHRT_MAX];
};

struct Stack *Stack_create()
{
    struct Stack *stack = malloc(sizeof(struct Stack));
    stack->length = 0;
    return stack;
}

void Stack_destroy(struct Stack *stack)
{
    free(stack);
}

void Stack_push(struct Stack *stack, void *val)
{
    stack->members[stack->length] = val;
    stack->length++;
}

void *Stack_pop(struct Stack *stack)
{
    if (stack->length == 0) return NULL;

    void *val = stack->members[stack->length - 1];
    stack->members[stack->length - 1] = NULL;
    stack->length--;
    return val;
}

int main(int argc, char *argv[])
{
    struct Stack *stack = Stack_create();
    int one = 1;
    int two = 2;
    int three = 3;

    Stack_push(stack, &one);
    Stack_push(stack, &two);
    Stack_push(stack, &three);

    printf("%d\n", *(int *)Stack_pop(stack));
    printf("%d\n", *(int *)Stack_pop(stack));
    printf("%d\n", *(int *)Stack_pop(stack));

    Stack_destroy(stack);

    return 0;
}

