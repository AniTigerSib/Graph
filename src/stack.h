#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

#define DEFINE_STACK(T)\
typedef struct NodeTag_##T {\
    T value;\
    struct NodeTag_##T *next;\
} NodeT_##T;\
typedef struct Stack_##T {\
    NodeT_##T *head;\
    size_t count;\
} Stack_##T;\
typedef Stack_##T Stack;\
Stack_##T* CreateStack();\
void Push(Stack_##T *stack, T value);\
NodeT_##T* PopNode(Stack_##T *stack);\
T PopValue(Stack_##T *stack);\
T Peek(Stack_##T *stack);\
void FreeStack(Stack_##T **stack);

#define DEFINE_STACK_METHODS(T)\
Stack_##T* CreateStack_##T() {\
    Stack_##T *stack = NULL;\
    stack = (Stack_##T *)malloc(sizeof(Stack_##T));\
    memset(stack, 0, sizeof(Stack_##T));\
    stack->head = NULL;\
    stack->count = 0;\
    return stack;\
}\
void Push_##T(Stack_##T *stack, T value) {\
    if (stack == NULL) {\
        return;\
    }\
    NodeT_##T *tmp = (NodeT_##T *)malloc(sizeof(NodeT_##T));\
    if (tmp == NULL) {\
        return;\
    }\
    tmp->next = stack->head;\
    tmp->value = value;\
    stack->head = tmp;\
    stack->count++;\
}\
NodeT_##T* PopNode_##T(Stack_##T *stack) {\
    if (stack == NULL || stack->head == NULL) {\
        return NULL;\
    }\
    NodeT_##T *out = NULL;\
    out = stack->head;\
    stack->head = stack->head->next;\
    stack->count--;\
    return out;\
}\
T PopValue_##T(Stack_##T *stack) {\
    if (stack == NULL || stack->head == NULL) {\
        return 0;\
    }\
    NodeT_##T *out = NULL;\
    T value;\
    out = PopNode_##T(stack);\
    if (out != NULL) {\
        value = out->value;\
        free(out);\
        return value;\
    }\
    return 0;\
}\
T Peek_##T(Stack_##T *stack) {\
    if (stack == NULL || stack->head == NULL) {\
        return 0;\
    }\
    return stack->head->value;\
}\
void FreeStack_##T(Stack_##T **stack) {\
    if (stack == NULL || *stack == NULL) {\
        return;\
    }\
    while ((*stack)->count) {\
        PopValue_##T(*stack);\
    }\
    free(*stack);\
    *stack = NULL;\
}\

// typedef char T;
// typedef struct Node_tag {
//     T value;
//     struct Node_tag *next;
// } Node_t;

// typedef struct Stack {
//     Node_t *head;
//     size_t count;
// } Stack;

// Stack* CreateStack();
// void Push(Stack *stack, T value);
// Node_t* PopNode(Stack *stack);
// T PopValue(Stack *stack);
// T Peek(Stack *stack);
// void FreeStack(Stack **stack);
int Priority(char symbol);

#endif