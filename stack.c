#include "stack.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include<stdlib.h>
#define STACKSIZE 100
int getPriority(StackElem operater) {
    int ret;
    if (operater == '+' || operater == '-') {
        ret = 1;
    }
    else if (operater == '*' || operater == '/') {
        ret = 2;
    }
    else {
        ret = 0;
    }
    return ret;
}

void postfixNotation(char* output, char* expression) {
    char nowChar;
    StackElem temp;
    int i;
    int outputNumber = 0;
    Stack operation;
      init_stack(&operation);

    for (i = 0; i < strlen(expression); i++) {
        nowChar = expression[i];
        if (isdigit(nowChar) || nowChar == '.') {
            while (isdigit(expression[i]) || expression[i] == '.') {
                output[outputNumber++] = expression[i++];
            }
            i--;
            output[outputNumber++] = ' ';
        } else if (nowChar == '(') {
            temp = nowChar;
            stack_push(&operation, &temp);
        } else if (nowChar == ')') {
            while (stack_get_top(&operation, &temp) == OK && temp != '(') {
                stack_pop(&operation, &temp);
                output[outputNumber++] = temp;
                output[outputNumber++] = ' ';
            }
        } else if (nowChar == '+' || nowChar == '-' || nowChar == '*' || nowChar == '/') {
            while (stack_get_top(&operation, &temp) == OK && getPriority(nowChar) <= getPriority(temp)) {
                stack_pop(&operation, &temp);
                output[outputNumber++] = temp;
                output[outputNumber++] = ' ';
            }
            temp = nowChar;
            stack_push(&operation, &temp);
        }
    }

    while (!is_empty(&operation)) {
        stack_pop(&operation, &temp);
        output[outputNumber++] = temp;
        output[outputNumber++] = ' ';
    }
    output[outputNumber] = '\0';
    stack_free(&operation);
}

Status init_stack(Stack* pStack) {
    pStack->pBase = (StackElem*)malloc(sizeof(StackElem) * STACKSIZE);
    if (!pStack->pBase) {
        return ERROR;
    }
    pStack->pTop = pStack->pBase;
    pStack->size = STACKSIZE;
    return OK;
}

void stack_free(Stack* pStack) {
    if (pStack->pBase) {
        free(pStack->pBase);
                pStack->pTop = pStack->pBase = NULL;
        pStack->size = 0;
    }
}

Bool is_empty(Stack* pStack) {
    return (pStack->pBase == pStack->pTop) ? TRUE : FALSE;
}

int stack_length(Stack* pStack) {
    return (pStack->pTop - pStack->pBase);
}

Status stack_get_top(Stack* pStack, StackElem* pElem) {
    if (is_empty(pStack)) {
        return ERROR;
    }
    else {
        *pElem = *(pStack->pTop - 1);
        return OK;
    }
}
Status stack_push(Stack* pStack, StackElem* pElem) {
    if (pStack->pTop - pStack->pBase == pStack->size) {
        return ERROR;
    }
    else {
        *(pStack->pTop) = *pElem;
        pStack->pTop++;
        return OK;
    }
}

Status stack_pop(Stack* pStack, StackElem* pElem) {
    if (is_empty(pStack)) {
        return ERROR;
    }
    else {
        pStack->pTop--;
        *pElem = *(pStack->pTop);
        return OK;
    }
}
StackElem calculatePostfix(const char* postfix) {
    Stack calculateStack;
    init_stack(&calculateStack);
    int i;
    StackElem num;
    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i]) || postfix[i] == '.') {
            num = atof(&postfix[i]);
            stack_push(&calculateStack,&num);
            while (isdigit(postfix[i])||postfix[i]=='.') {
                i++;
            }
            i--;
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            StackElem calculate2, calculate1;
            stack_pop(&calculateStack, &calculate1);
            stack_pop(&calculateStack, &calculate2);
            StackElem result;
            if (postfix[i] == '+') {
                result = calculate1 + calculate2;
            }
            else if (postfix[i] == '-') {
                result = calculate2 - calculate1;
            }
            else if (postfix[i] == '*') {
                result = calculate1 * calculate2;
            }
            else if (postfix[i] == '/') {
                if (calculate1 == 0.0) {
                    printf("错误:0不能作除数\n");
                    exit(1);
                }else{
                result = calculate2 / calculate1;
                }
            }
            stack_push(&calculateStack, &result);
        }
    }
    StackElem finalResult;
    stack_pop(&calculateStack, &finalResult);
    return finalResult;
}
void printHelp() {
    printf("计算机使用帮助:\n");
    printf("输入一个表达式来计算,可用符号: +, -, *, /和()\n");
     printf("输入quit退出计算机\n");
    printf("输入help提示帮助信息\n");
    printf("输入CTRL+U清除当前行\n");
    printf("使用↑ 和 ↓ 键来查看历史记录\n");
}
