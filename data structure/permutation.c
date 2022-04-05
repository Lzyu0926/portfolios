
#include <stdio.h>

void swap(char *a,char *b){
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void permutation(char arr[],int first,int last){
    if(first == last){
        for(int i=0;i<3;i++)
            printf("%c",arr[i]);
        printf("\n");
    }
    else{
        for(int i = first;i<3;i++){
            swap(&arr[i],&arr[first]);
            permutation(arr,first+1,last); //{$a,b,c}->{a,$b,c}
            swap(&arr[i],&arr[first]);
        }
    }
}



int main(){
    char arr[3]={'a','b','c'};
    for(int i = 0;i<3;i++){
        permutation(arr,i,2);
    }
    
}

