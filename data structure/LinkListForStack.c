#include<stdio.h>
#include<stdlib.h>


typedef struct node{
    int data;
    struct node *next;
}Node;

void push(int d, Node *top){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = d;
    newNode->next = top;
    top = newNode
    
}

void pop(int d, Node *top){
    
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

    Node *Top = NULL;
    
    push(3,Top);
    
    

}