/*
請完成一程式，程式內容如下：
程式從標準輸入逐行讀入，
輸入內容為 Infix 則輸出為 Postfix 轉換結果
輸入內容為 Postfix 則輸出計算結果

每筆輸入首行為 "p: " 或 "i: " 代表該行輸入是 postfix 或是 infix。
每行長度不超過 1024 個 byte。
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

int infix_to_postfix(char *p, char *op);

int postfix_to_answer(char *p, char *op);

char *get_word(char *t, char *w);

char *get_op_word(char *t, char *w);

int calculate(int a, int b, char op);

int level(char oper);

int main() {

    char line[MAX];
    char word[256];
    int postfix_answer;
    char *ptr = NULL;

    while (fgets(line, MAX, stdin) != NULL) {
        ptr = line;
        /* 取第一個字*/
        ptr = get_word(ptr, word);
        // printf("first: %s\n", word);
        if (memcmp(word, "i:", 3) == 0) {
            infix_to_postfix(ptr, word);
        } else if (memcmp(word, "p:", 3) == 0) {
            postfix_answer = postfix_to_answer(ptr, word);
            printf("%d\n", postfix_answer);
        } else {
            return 0;
        }

    }

}

char *get_word(char *t, char *w) {
    char *p = t;
    char *q = w;
    *w = '\0';

    while (*p && isspace(*p)) {
        p++;
    }
    while ((*p && !isspace(*p))) {
        *q++ = *p++;
    }
    *q = '\0';
    if (*w == '\0') {
        return NULL;
    } else {
        return p;
    }
}

char *get_op_word(char *t, char *w) {
    char *p = t;
    char *q = w;
    *w = '\0';

    while (*p && isspace(*p)) {
        p++;
    }
    while ((*p && !isspace(*p)) && (*p == '(' || *p == ')' || *p == '+' || *p == '-' || *p == '*' || *p == '/')) {
        *q++ = *p++;
        *q = '\0';
        if (*w == '\0') {
            return NULL;
        } else {
            return p;
        }
    }
    while ((*p && !isspace(*p)) && isdigit(*p)) {
        *q++ = *p++;
    }
    *q = '\0';
    if (*w == '\0') {
        return NULL;
    } else {
        return p;
    }
}

int infix_to_postfix(char *p, char *op) {
    char postfix[MAX][256] = {'\0'};
    char stack[MAX] = {'\0'};
    int top = 0;
    int post_cnt = 0;
    char *pi;

    pi = p;
    while ((pi = get_op_word(pi, op)) != NULL) {
//        printf("top: %d\n", top);
//        printf("words: %s\n", op);
        switch (*op) {
            case '(':
//                printf("*op: %c\n", *op);
                stack[++top] = *op;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
//                printf("*op: %c\n", *op);
                while (top && level(stack[top]) >= level(*op)) {
//                    printf("hi\n");
                    postfix[post_cnt++][0] = stack[top--];
                }
                stack[++top] = *op;
//                printf("top: %d\n", top);
                break;
            case ')':
                while (stack[top] != '(') {
                    postfix[post_cnt++][0] = stack[top--];
                }
//                printf("*op: %c\n", *op);
                top--;
                break;
            default:
                strcpy(postfix[post_cnt++], op);
                break;
        }
    }
    while (top) {
        // printf("%s\n", stack);
        postfix[post_cnt++][0] = stack[top--];
    }
    for (int i = 0; i < post_cnt; ++i) {
        printf("%s ", postfix[i]);
    }
    printf("\n");
    return 1;
}

int postfix_to_answer(char *p, char *op) {

    int stack[MAX] = {'\0'};
    char *pi = p;
    int top = 0;
    int conclusion = 0;

    while ((pi = get_op_word(pi, op)) != NULL) {
//        printf("words: %s\n", op);
        switch (*op) {
            case '+':
            case '-':
            case '*':
            case '/':
                conclusion = calculate(stack[top - 1], stack[top], *op);
                stack[--top] = conclusion;
                break;
            default:
                stack[++top] = atoi(op);
                break;
        }
//        printf("stack: %d\n", stack[top]);

    }


    return stack[top];
}

int calculate(int a, int b, char op) {

    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            break;
    }
    return 0;
}

int level(char oper) {

    if (oper == '*' || oper == '/') {
        return 2;
    } else if (oper == '+' || oper == '-') {
        return 1;
    } else {
        return 0;
    }
}