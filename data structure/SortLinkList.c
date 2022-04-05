/*
請同學在原來作業四的程式碼加上排序功能，透過呼叫 standard library 中的 qsort() function 完成實做，按照 term count 由大到小或由小到大輸出。
(每筆測資的 term count 皆不同，不須考慮排序穩定性問題)
從 argv 給定參數，若 argv[1] 為 "asc" 請同學以小到大排序輸出。
若 argv[1] 為 "desc" 請同學以大到小排序輸出。
其餘要求皆與作業四相同，請同學以 linked list 實做，並記得呼叫 free() 完成記憶體釋放。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024


typedef struct term {
    char *word;
    int cnt;
    struct term *next;
} Term;

int rm_n(char line[]);

Term *make_new_node();

int put_in_arr(Term *np, int *arr);

int cmp_max_to_min(const void *a, const void *b);

int cmp_min_to_max(const void *a, const void *b);

void printout(int *arr, Term *np, int arr_len, Term *head);

void end(Term *np, Term *head);

int main(int argc, char **argv) {

    char line[MAX];
    int word_len;
    int *arr = malloc(MAX);
    int items;


    Term *head = malloc(sizeof(Term));
    if (head == NULL) {
        puts("配置錯誤");
    }
    head->next = NULL;
    Term *np = head;
    np->word = malloc(1024);
    np->next = NULL;

    while (fgets(line, MAX, stdin) != NULL) {
        word_len = rm_n(line);
        np = head;
        if (line[0] == '-') {
            np = np->next;
            while (np) {
                if (strcmp(line+1, np->word) == 0) {
                    np->cnt--;
                    break;
                }
                np = np->next;
            }
        } else {
            while (np) {
                if (memcmp(np->word, line, word_len) == 0) {
                    np->cnt++;
                    break;
                }
                if (!np->next) {
                    np->next = make_new_node();
                    np = np->next;
                    np->word = malloc(word_len + 1);
                    memcpy(np->word, line, word_len);
                    break;
                }
                np = np->next;
            }
        }

    }
    np = head;
    np = np->next;
    items = put_in_arr(np, arr);

    np = head;
    np = np->next;

    if (strcmp(argv[1], "desc") == 0) {
        qsort(arr, items, sizeof(int), cmp_max_to_min);
        printout(arr, np, items, head);
    } else {
        qsort(arr, items, sizeof(int), cmp_min_to_max);
        printout(arr, np, items, head);
    }
    end(np, head);

}

int rm_n(char line[]) {
    size_t len;
    len = strlen(line);
    if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
    return strlen(line);
}

Term *make_new_node() {
    Term *new_node = malloc(sizeof(Term));
    new_node->cnt = 1;
    new_node->next = NULL;
    return new_node;
}

int put_in_arr(Term *np, int *arr) {
    int i = 0;
    while (np) {
        *(arr + i) = np->cnt;
        np = np->next;
        i++;
    }
    return i;

}

int cmp_max_to_min(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}

int cmp_min_to_max(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

void printout(int *arr, Term *np, int arr_len, Term *head) {
    for (int i = 0; i < arr_len; i++) {
        np = head;
        np = np->next;
        while (np) {
            if (np->cnt == *(arr + i)) {
                printf("%s: %d\n", np->word, np->cnt);
                np->cnt = 0;
                break;
            }
            np = np->next;
        }
    }
}

void end(Term *np, Term *head) {
    np = head;
    np = np->next;
    while (np) {
        Term *temp;
        temp = np->next;
        free(np->word);
        free(np);
        np = temp;
    }
}