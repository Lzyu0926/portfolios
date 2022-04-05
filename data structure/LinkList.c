#include<stdio.h>
#include<stdlib.h>


typedef struct node{
    int data;
    struct node *next;
}Node;

void insert(int d, Node *r){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = d;
    newNode->next = NULL;
    Node *ptr = r;
    while (ptr->next)
    {
        ptr = ptr->next;
    }
    ptr->next = newNode;
}

void delet(int d, Node *r){
    Node *ptr = r;
    ptr = ptr->next;
    Node *tmp = r;
    while (ptr)
    {   
        if(ptr->data==d){
            tmp->next = ptr->next;
            ptr = ptr->next;
            continue;
        }
        tmp = ptr;
        ptr = ptr->next;
    }
}

void show(Node *r){
    Node *ptr = r;
    ptr = ptr->next;
    while (ptr)
    {
        printf("%d",ptr->data);
        ptr = ptr->next;
        if(ptr)
            printf("->");
    }
    printf("\n");
}
int main(){

    Node *root = malloc(sizeof(Node));
    root->next = NULL;
    for(int i  = 0;i<10;i++){
        insert(3,root);
    }
    for(int i  = 0;i<10;i++){
        insert(i,root);
    }
    show(root);
    delet(3,root);
    show(root);
    
    

}