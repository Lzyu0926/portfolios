
/*
Description
撰寫一程式，使用 Binary Search Tree (BST) 進行單詞統計，每個節點儲存單字及單字數量。
BST 須符合每個節點中左子樹所有節點字串小於該節點字串，右子樹所有節點字串大於該節點字串。

程式流程
    1.如果輸入之單字為單字則插入 BST ，若已在 BST 裡則新增或減少單字數量。
    2.使用 inorder traversal 方式輸出 BST 的內容。
    3.將 BST 轉成 array 後，進行排序。
        a.比較方式為單字數量大的在前面，小的在後面
        b.數量一樣則以字串 ASCII 碼較小的在前面。
    4.輸出排序後內容
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DATA_SIZE 1024
#define is_decrease(src_data) \
            src_data[0]=='-'
typedef struct arr{
    int cnt;
    char string[100];
    int flag;
}ARR;

typedef struct bst {
    char *data;
    int cnt;
    struct bst *left_node;
    struct bst *right_node;
} BST;

void node_find(BST *head, BST *np, char *src_data,int dec);

void node_insert(BST *np, char *src_data, int direct);

void bst_inorder_traversal(BST *np,ARR buff[],int *buff_cnt);

BST *new_node();

void node_init(BST *np);

void bst_free(BST *np);

void print_sorted_arr(int buff_cnt,int buff_arr[],ARR *buff);

int cmp(const void *a, const void *b);

int main() {
    char src_data[DATA_SIZE];
    int dec = 0; // 方向 0 是左 1 是右
    int first_insert = 0;

    BST *head = malloc(sizeof(BST));
    BST *np = head;

    node_init(np);

    ARR buff[DATA_SIZE];
    int buff_cnt = 0;
    int *ptr_cnt = &buff_cnt;
    int buff_arr[DATA_SIZE] = {'\0'};
    
    while (fgets(src_data, DATA_SIZE, stdin)) {
        src_data[strcspn(src_data, "\n\r")] = '\0';
        /*===== first insert only do once  =====*/
        if(!first_insert){
            strcpy(np->data,src_data);
            first_insert = 1;
            np->cnt++;
            continue;
        }

        if (is_decrease(src_data)) {
            dec = 1;
            node_find(head, np, src_data+1,dec);
        } else{
            dec = 0;
            node_find(head, np, src_data,dec);
        }

    }
    /*=====  inorder traversal  =====*/
    np = head;
    puts("Inorder traversal:");
    bst_inorder_traversal(np,buff,ptr_cnt);
    puts("");

    // put in arr
    for(int i = 0; i<buff_cnt;i++){
        buff_arr[i] = buff[i].cnt;
    }
    puts("Count sorting:");
    /*=====  sorting  =====*/
    qsort(buff_arr,*ptr_cnt, sizeof(int),cmp);
    /*=====  print the sort arr  =====*/
    print_sorted_arr(buff_cnt,buff_arr,buff);
    /*=====  free  =====*/
    np = head;
    bst_free(np);

}


void node_init(BST *np) {
    np->data = malloc(DATA_SIZE);
    np->left_node = NULL;
    np->right_node = NULL;
    np->cnt = 0;
}

void node_find(BST *head, BST *np, char *src_data, int dec) {
    int direct;
    np = head;
    while (np) {
        if (strcmp(np->data, src_data) < 0) {
            if (!np->right_node) {
                direct = 1;
                node_insert(np, src_data, direct);
                return;
            } else {
                np = np->right_node;
                continue;
            }
        } else if (strcmp(np->data, src_data) > 0) {
            if (!np->left_node) {
                direct = 0;
                node_insert(np, src_data, direct);
                return;
            } else {
                np = np->left_node;
                continue;
            }
        } else if(dec){
            np->cnt--;
            return;
        } else{
            np->cnt++;
            return;
        }
    }
}

void node_insert(BST *np, char *src_data, int direct) {

    if (direct) {
        np->right_node = new_node();
        np = np->right_node;
        node_init(np);
        strcpy(np->data, src_data);
        np->cnt++;
    } else {
        np->left_node = new_node();
        np = np->left_node;
        node_init(np);
        strcpy(np->data, src_data);
        np->cnt++;
    }

}

BST *new_node() {
    BST *new_np = malloc(sizeof(BST));
    return new_np;
}

void bst_inorder_traversal(BST *np, ARR buff[],int *buff_cnt){
    if(np){
        bst_inorder_traversal(np->left_node,buff,buff_cnt);
        printf("%d %s\n",np->cnt,np->data);
        buff[*buff_cnt].cnt = np->cnt;
        buff[*buff_cnt].flag = 0;
        strcpy(buff[(*buff_cnt)++].string,np->data);
        bst_inorder_traversal(np->right_node,buff,buff_cnt);
    }

}

int cmp(const void *a, const void *b){
    return   *(int*)b - *(int*)a;
}

void print_sorted_arr(int buff_cnt,int buff_arr[],ARR *buff){
    for(int i = 0; i<buff_cnt;i++){
        for(int j = 0; j<buff_cnt;j++){
            if(buff_arr[i] == buff[j].cnt && !buff[j].flag){
                printf("%d %s\n",buff[j].cnt,buff[j].string);
                buff[j].flag = 1;
            }
        }
    }
}
void bst_free(BST *np){
    if(np){
        bst_free(np->left_node);
        bst_free(np->right_node);
        free(np);
    }
}