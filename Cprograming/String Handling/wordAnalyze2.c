/*
給定一篇來自野生的英文新聞文章，請輸出以下內容：
1. 如果第一個單字在該行中出現兩次以上，則輸出該行
2. 輸出最長單字以及其長度
    a.若有相同長度的單字，則按照出現時間依序輸出；若有重複的單字則略過，參考範例輸出。
3. 輸出文章中所有單字 (以空白(White space)、逗號(,)、句號(.)、雙引號(")、冒號(:)、驚嘆號(!)、問號(?)、左括號 '(' 以及右括號 ')' 做分隔)
    a. 按照單字出現時間依序輸出，參考範例輸出
並依照輸出說明進行輸出。
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_WORD 1000

int get_word(char text[],int offset, char word[]);
void remove_new_line_symbol(char curr_line[]);
void get_first_word(char text2[],char first_word[]);
void first_word_occur_second(char the_word_occur_second[],char first_word[]);
int get_maxlen_word_and_len(char max_len_word[][MAX_LINE_WORD], int *the_max_word_len, int max_len_word_count, char word[], int word_len);




int main(){
    
    char curr_line[MAX_LINE_WORD];
    char word[MAX_LINE_WORD] = {0};//最多1000字
    char first_word[MAX_LINE_WORD] = {0};
    char max_len_word[MAX_LINE_WORD][MAX_LINE_WORD] = {0};
    char word_arr[MAX_LINE_WORD][MAX_LINE_WORD];
    char line_arr[MAX_LINE_WORD][MAX_LINE_WORD];
    
    int first_word_equal_other_count = 0;
    
    
    int offset = 0; //平移量
    int curr_line_length = 0;
    int count_line = 0;
    int word_len = 0;
    int the_max_word_len = 0;
    int max_len_word_count = 0;
    int line_arr_cnt = 0;
    int total_count_line = 0;
    
    int total_word = 0;
    int i = 0;
    int j = 0;
    
    while (fgets(curr_line, MAX_LINE_WORD, stdin)) {
        /*================移除\n====================*/
        remove_new_line_symbol(curr_line);
        /*================得到第一個字====================*/
        get_first_word(curr_line,first_word);
        /*=================印出所有單字，印出與第一字重複的句子=======================*/
        curr_line_length = strlen(curr_line);
        offset = 0;
        while (offset < curr_line_length) {                       //當平移量小於行度長
            offset = get_word(curr_line, offset, word);
            word_len = strlen(word);
            if(strcmp(word, first_word) == 0){
                count_line++;
            }
            max_len_word_count = get_maxlen_word_and_len( max_len_word, &the_max_word_len,  max_len_word_count,  word,  word_len);
            
            if(word_len != 0){
                strcpy(word_arr[line_arr_cnt++],word);
                total_word ++;
            }
            
        }
        
        
        if(count_line >= 2){
            first_word_equal_other_count++;
            strcpy(line_arr[i++],curr_line);
        }
       
        count_line = 0;
    }
    
    printf("--- [0] The line that the first word occurs more than twice in the line ---\n");
    if ( first_word_equal_other_count > 0) {
        printf("Repeated line count: %d\n",first_word_equal_other_count);
        for (int i = 0;  i < first_word_equal_other_count; i++) {
            printf("[%d]: %s",i,line_arr[i]);
        }
    }
    else{
        printf("It is not exist!\n");
    }

    printf("--- [1] The longest words and their length ---\n");
    printf("Word length: %d\n",the_max_word_len);
    for ( int i = 0; i < max_len_word_count ; i++) {
        printf("[%d]: %s\n",i,max_len_word[i]);
    }
    printf("--- [2] The words appear in the article ---\n");
    printf("Total words: %d\n",total_word);
    for ( int i = 0; i < total_word; i++) {
        printf("%s ",word_arr[i]);
        j++;
        if(j == 10){
            printf("\n");
            j = 0;
        }
    }
}


/*=====得到第一個字=====*/
void get_first_word(char text2[],char first_word[]){
    int x = 0;
    int y = 0;
    while (isspace(text2[x])) {
           x++;
    }
    while (text2[x] == ','|| text2[x] == '.'|| text2[x] == '"'|| text2[x] == ':'|| text2[x] == '!'
    || text2[x] == '?'|| text2[x] == '('|| text2[x] == ')') {
        x++;
    }
    while (!isspace(text2[x])) {
        if (text2[x] == ','|| text2[x] == '.'|| text2[x] == '"'|| text2[x] == ':'|| text2[x] == '!'
        || text2[x] == '?'|| text2[x] == '('|| text2[x] == ')') {
            break;
        }
        else{
        first_word[y++] = text2[x++];
        }
    }
    first_word[y] = '\0';
}



void remove_new_line_symbol(char curr_line[]){
    int length;
    length = strlen(curr_line);
    curr_line[length] = '\0';
}

            /*=====切字=====*/
int get_word(char text[],int offset, char word[]){
    int k ;
    int i ;
    i = offset;
    k = 0;

    while((isspace(text[i]))){
        i++;
    }
    while (text[i] == ','|| text[i] == '.'|| text[i] == '\"'|| text[i] == ':'|| text[i] == '!'
    || text[i] == '?'|| text[i] == '('|| text[i] == ')') {
        i++;
    }
    while(!isspace(text[i])){
        if (text[i] == ','|| text[i] == '.'|| text[i] == '\"'|| text[i] == ':'|| text[i] == '!'
        || text[i] == '?'|| text[i] == '('|| text[i] == ')') {
            break;
        }
        else{
            word[k] = text[i];
            k++;
            i++;
        }
    }
    word[k] = '\0';

    return  i;
}


int get_maxlen_word_and_len(char max_len_word[][MAX_LINE_WORD], int *the_max_word_len, int longest_word_count, char word[], int word_len){
    if(word_len > *the_max_word_len){
        longest_word_count=0;
        *the_max_word_len = word_len;
        strcpy(max_len_word[longest_word_count], word);
        longest_word_count++;
    } else if(word_len == *the_max_word_len && strcmp(max_len_word[0], word) != 0){
        strcpy(max_len_word[longest_word_count], word);
        longest_word_count++;
    }
    return longest_word_count;
}
            



