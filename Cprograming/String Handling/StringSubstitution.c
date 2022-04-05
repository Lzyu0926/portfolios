/*
撰寫一程式，使用方式如下：

./sed  [ -g(optional) ]  [ -source(required) ]  [ -target(required) ]

程式從標準輸入逐行讀入，將每行第一個出現 [ -source ] 字串的地方取代為 [ -target ] 字串。

若 [ -g ] 被啟用，則將每行所有出現  [ -source ] 字串的地方取代為 [ -target ] 字串。

[ -source ] 與 [ -target ] 長度介於 1 ~ 256 之間，且每行不超過 1024 個 byte。

將取代結果於標準輸出印出。

輸入及輸出每行皆以換行符號( '\n' ) 結尾。

若輸入的參數有 2 個，參數依序為 [ -source ] 與 [ -target ]，

若輸入的參數有 3 個，參數依序為 [ -g ]、[ -source ] 與 [ -target ]，

任何未定義的操作需印出 help message，詳細請參考範例輸出。

./sed 是執行檔名稱
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 2048
void usage();
int main(int argc,char **argv){
    char *line = malloc(MAXLINE);
    char *after_line = malloc(MAXLINE);
    char *dest = NULL;
    int target_len;
    int src_len;
    /*--------test---------*/
    // for(int i=0; i < argc;i++){
    //     printf("argv[%d]: %s\n",i,*(argv+i));
    // }
    // 
    if(argc >=4 && strcmp("-g",*(argv+1))!=0){
        usage();
    }
    else if(argc<=2){
        usage();

    }
    else{
        while(fgets(line,MAXLINE,stdin)!=NULL){
        // puts("hi i am here");
        // printf("line: %s",line);
            if(argc == 4){
                if(strcmp("-g",*(argv+1))==0){
                  target_len = strlen(*(argv+3));
                  src_len = strlen(*(argv+2));
                // printf("target len %d\n",target_len);
                // printf("source len %d\n",src_len);
                  dest = strstr(line,*(argv+2));
                 while(dest != NULL){
                    // puts("hi");
                    strcpy(after_line,dest+src_len);
                    strcpy(dest,*(argv+3));
                    strcat(line,after_line);
                    dest = strstr(line,*(argv+2));
                    // printf("%s",line);
                }
                printf("%s",line);
            }
            else{
                usage();
                }   
            }
        else if(argc==3){
            target_len = strlen(*(argv+2));
            src_len = strlen(*(argv+1));
            // printf("target len %d\n",target_len);
            dest = strstr(line,*(argv+1));
            // printf("%p\n",dest);
            // printf("%s\n",dest+5);
            if(dest != NULL){
                strcpy(after_line,dest+src_len);
                  // printf("%s\n",after_line);
                  strcpy(dest,*(argv+2));
                  strcat(line,after_line);
            }
            printf("%s",line);

        }
        else{
            usage();
        }
    }
    }
    
    

}

void usage(){
    puts("Usage:");
    puts("./sed [-g(optional)] [-source(required)] [-target(required)]");
}

