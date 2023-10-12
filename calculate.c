#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "stack.h" // 包含辅助函数和函数声明

#define MAXSTRING 100
#define STACKSIZE 100

int main(int argc, char* argv[]) {
    char expression[MAXSTRING];
    char output[MAXSTRING];
    char history[MAXSTRING][MAXSTRING];
    int historySize = 0;
    int currentHistoryIndex = 0;

    char* outputFileName = NULL;
    FILE* outputFile = NULL;

    // Process command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                outputFileName = argv[i + 1];
                i++;
                            } else {
                fprintf(stderr, "错误:需带有文件名\n");
                return 1;
            }
        }
    }

    if (outputFileName != NULL) {
        outputFile = fopen(outputFileName, "w");
        if (outputFile == NULL) {
            fprintf(stderr, "错误:无法打开文件\n");
            return 1;
        }
    }

    while (1) {
        char* input = readline("输入一个计算表达式,或输入quit退出程序,输入help查看帮助: ");

        if (input == NULL) {
            break;
        }

        strncpy(expression, input, MAXSTRING);
       add_history(input);

        if (strcmp(input, "help") == 0) {
            printHelp();
        } else if (strcmp(input, "quit") == 0) {
            printf("已退出.\n");
            free(input);
            break;
        } else {
            postfixNotation(output, expression);
            double result = calculatePostfix(output);
            printf("结果是: %.2f\n", result);

            if (outputFile != NULL) {
                fprintf(outputFile, "表达式: %s\n结果: %.2f\n", expression, result);
            }
        }

        free(input);
    }

    if (outputFile != NULL) {
        fclose(outputFile);
    }

    return 0;
}
