#ifndef AI1_H
#define AI1_H

typedef enum { FALSE, TRUE } Bool;
typedef enum { ERROR, OK } Status;
typedef double StackElem;

typedef struct {
    StackElem* pBase;
    StackElem* pTop;
    int size;
} Stack;

Status init_stack(Stack* pStack);
void stack_free(Stack* pStack);
Bool is_empty(Stack* pStack);
int stack_length(Stack* pStack);
Status stack_get_top(Stack* pStack, StackElem* pElem);
Status stack_push(Stack* pStack, StackElem* pElem);
Status stack_pop(Stack* pStack, StackElem* pElem);
int getPriority(StackElem operater);
void postfixNotation(char* output, char* expression);
double calculatePostfix(const char* postfix);
void printHelp();

#endif
