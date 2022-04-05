
/*
給定一篇來自野生環境的英文新聞文章，請統計出以下內容：
1. 空格（Space）字元數（空格字元即為 ASCII 0x20 (32)） 
2. 空白（Whitespace）字元數（根據 http://www.cplusplus.com/reference/cctype/isspace/ 所定義的空白字元）
3. 小寫字母（Lowercase）數
4. 大寫字母（Uppercase）數
5. 數字（Digit）字數
6. 不分大小寫（Case-insensitive）字母數
7. 全篇幅 Bytes 數（提示：這也是這個檔案的大小）
8. 字詞（Word）數（以「空白（Whitespace）」為分隔點）
9. 總行（Line）數（行的定義為該行必須有多於 0 個字元，此方能成行
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define IN  1
#define OUT 0


int main() {
    int state;
    /* 數東西 */

    int count_bytes = 0;
    int count_line  = 1;
    int word_count  = 0;
    int space = 0;
    int whitespace = 0;
    int Uppercase_Count = 0;
    int lowercase_Count = 0;
    int digit_Count = 0;
    
    int new_line = 0;
    int in_word = 0;
    int maxword_len = 0;
    
    int lowers[26]={0};
    int uppers[26]={0};
    int digits[10]={0};
    
    char curr_word[100]={0};
    char max_word[100]={0};
   

    char c;

    while((c=getchar())!=EOF) {
        count_bytes++;

        /*算行*/
        //////////////////
        if(new_line == 1){
            count_line++;
            new_line = 0;
        }

        if(c == '\n'){
            new_line = 1;
        }
        //////////////////
        /*數空白*/
        if(!isspace(c)){
            state = IN;
            curr_word[in_word++] = c;
        }
        /*============================*/
        else{
          if (c==' ') {
            space++;
          }
          state = OUT;
          whitespace++;   
          
        }
        if (state == OUT) {
            curr_word[in_word] = '\0';
            if(in_word != 0){
                word_count++;
            }
            if((in_word>maxword_len) || (in_word == maxword_len && strcmp(curr_word,max_word)<0)){
                strcpy(max_word,curr_word);
                maxword_len = in_word;
            }
            in_word = 0;
            curr_word[in_word] = '\0'; 
        }
        
        /*數字母*/
        if('0'<=c&&c<='9'){
            digit_Count++;
            digits[c-'0']++;
            
        }
        else if('A'<=c&&c<='Z'){
            uppers[c-'A']++;
            Uppercase_Count++;
        }
        else if('a'<=c&&c<='z'){
            lowers[c-'a']++;
            lowercase_Count++;
        }   
    }
    /*===================================*/
    if (state == IN){
          curr_word[in_word] = '\0';
          if(in_word != 0){
               word_count++;
          }
          if((in_word>maxword_len) || (in_word == maxword_len && strcmp(curr_word,max_word)<0)){
              strcpy(max_word,curr_word);
              maxword_len = in_word;
          }
          in_word = 0;
          curr_word[in_word] = '\0';
    }


    
    printf("===\n"
           "[0] Overview Stats\n"
           "===\n"
           "Space Count: %d\n"
           "Whitespace Count: %d\n"
           "Lowercase Count: %d\n"
           "Uppercase Count: %d\n"
           "Digit Count: %d\n"
           "Case-insensitive Count: %d\n"
           "Byte Count: %d\n"
           "Word Count: %d\n"
           "Total Line: %d\n"
           "===\n"
           "[1] Longest Word\n"
           "===\n"
           "Word: %s\n"
           "Length: %d\n"
           "===\n"
           "[2] Case-Sensitive Stats\n"
           "===\n"
           ,space,whitespace,
           lowercase_Count,Uppercase_Count,
           digit_Count,Uppercase_Count+lowercase_Count,count_bytes,
           word_count,count_line,max_word,maxword_len
           );
        for(int i = 0; i <=25;i++){
            printf("%c: %d\t%c: %d\n",i+65,uppers[i],i+97,lowers[i]);
        }
        printf("===\n"
               "[3] Case-Insensitive Stats\n"
               "===\n");
        for(int i = 0; i <=25;i++){
            printf("%c: %d\n",i+97,uppers[i]+lowers[i]);
        }
        printf("===\n"
               "[4] Digit Stats\n"
               "===\n");
        for(int i = 0; i <=9; i++){
            printf("%d: %d\n",i,digits[i]);
        }       
    
    return 0;
}