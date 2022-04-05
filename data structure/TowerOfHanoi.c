#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void move(char a[],char b[]){
    int la = strlen(a);
    int lb = strlen(b);
    char tmp  = a[la-1];  
    a[la-1] = '\0';
    b[lb] = tmp;
}

void hanoi(int num,char src[],char tmp[],char dst[]){
    if(num==1){
        move(src,dst);
    }else{
        hanoi(num-1,src,dst,tmp);
        hanoi(1,src,tmp,dst);
        hanoi(num-1,tmp,src,dst);
    }
    

}

int main(){
    char A[5] = {'1','2','3','4','\0'};
    char B[5] ={'\0'};
    char C[5] ={'\0'};

    hanoi(4,A,B,C);

    printf("%s",C);
}