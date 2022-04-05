/*
通訊錄程式
請完成一通訊錄程式可以記錄  姓名 、 email 、 網頁連結 及 手機號碼  並包含以下功能:

創建通訊錄
根據程式參數 argv[1]，新建 N 個聯絡人的通訊錄
N 筆輸入，格式為  <name>\t<email>\t<url>\t<phone_number> 
創建完後進入指令模式 

新增聯絡人 (i)
格式: i\t<name>\t<email>\t<url>\t<phone_number> 
功能: 在通訊錄最後一筆後面插入新的聯絡人，資料中間以 \t 隔開，資料不會有空值。
ex: i jack jack@email.example hello.world.tw 987654321 (新增 jack 聯絡人)

更新聯絡人 (u)
格式: u\t<name>\t<email>\t<url>\t<phone_number> 
功能: 更新既有聯絡人資訊，資料中間以 \t 隔開，資料不會有空值。
ex: u jack jack123@email.email hello.world.tw 123456789 (更新 jack 聯絡人資訊)

刪除聯絡人 (d)
格式:  d\t<name> 
功能:  刪除特定聯絡人
ex:  d jack  (刪除 jack)

找尋 (f)
格式:  f\t<pattern> 
功能: 找尋有 <pattern> 的聯絡人，<pattern> 有分大小寫。
     若有找到符合的聯絡人，則輸出聯絡人資訊；沒有則需輸出沒有結果 (見範例輸出)
ex: f jack (找尋 jack 以及名字裡含 jack 的聯絡人，例如: jack, jack_son, man_jack等等 ) 

	f j(找尋有 j 字母的聯絡人)

排序 (s)
格式:  s\t<pattern> 
功能:  以 <pattern> 欄位從小到大排序 (僅排序，不須輸出)。
    欄位分為 n (姓名) 、 e (email) 、 u (網址) 、 p (手機號碼)
    手機號碼以數值排序 (可使用  atoi() )，其餘以 ASCII 碼值做比較
ex: s n (將通訊錄以名字從小到大排序)

顯示通訊錄內容 (p)
格式: p 
功能: 以特定格式輸出通訊錄
ex: (見範例輸出)

離開程式 (q, quit)
格式: q 、 quit 
功能: 結束程式
ex: q
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1024
#define MAPEOPLE 1024

enum {
    NAME, EMAIL, URL, PHONE
};
/*-----<name>\t<email>\t<url>\t<phone_number>-----*/
struct file {
    char name[MAPEOPLE][32];
    char email[MAPEOPLE][128];
    char url[MAPEOPLE][128];
    char phone[MAPEOPLE][16];
};
typedef struct file File;


char *get_word(char *t, char *w);

char *get_second_word(char *p, char *w);

void insert_instruction(File *student, char *p, char *w, int stu_cnt);

void update_instruction(File *student, int target, char *p, char *w);

void delete_instruction(File *student, char *target, int stu_cnt);

void find_instruction(File *output, char *w, int stu_cnt);

void sort_instruction(File *output, char *w, int stu_cnt);

void print_instruction(File *output, int stu_cnt);

void sort_copy(File *output,int i, int j);

int main(int argc, char **argv) {

    /*get word*/
    char *line = malloc(MAXLINE);
    char *word = malloc(MAXLINE/2);
    char *ptr = NULL;
    /*structure*/
    File student;


    int word_cnt = 0;
    int stu_cnt = 0;


    if (argc == 1 || argc > 2 || atoi(argv[1]) == 0) {
        return 0;
    }


    int stu_number = atoi(argv[1]);
    
    // printf("%d\n",stu_number);
    while (fgets(line, MAXLINE, stdin) != NULL) {
        ptr = line;
        word_cnt = 0;
        /*get word , first time input*/
        while ((ptr = get_word(ptr, word)) != NULL) {
        //    printf("%s\n",word);
            word_cnt++;
        }
        ptr = line;
        if (word_cnt == 4 && stu_cnt < stu_number) {           
                for (int i = 0; i < 4 && (ptr = get_word(ptr, word)) != NULL; i++) {
                    if (i == NAME) {
                        strcpy(student.name[stu_cnt], word);
                    } else if (i == EMAIL) {
                        strcpy(student.email[stu_cnt], word);
                    } else if (i == URL) {
                        strcpy(student.url[stu_cnt], word);
                    } else if (i == PHONE) {
                        strcpy(student.phone[stu_cnt], word);
                    } else {
                        return 0;
                    }
                }
                stu_cnt++;

        }
        if (word_cnt == 5) {
            if (line[0] == 'i') {
                insert_instruction(&student, ptr, word, stu_cnt);
                stu_cnt++;
            } else if (line[0] == 'u') {
                ptr = get_second_word(ptr, word);
                for (int i = 0; i < stu_cnt; i++) {
                    if (strcmp(student.name[i], word) == 0) {
                        update_instruction(&student, i, ptr, word);
                    }
                }
            } else {
                puts("錯誤");
            }
        }
        if (word_cnt == 1) {
            if (line[0] == 'p') {
                print_instruction(&student, stu_cnt);
            } else if (line[0] == 'q' || strcmp(line, "quit") == 0) {
                return 0;
            } else {
                puts("錯誤");
                return 0;
            }
        }

        if (word_cnt == 2) {
            ptr = get_second_word(ptr, word);
//            printf("word: %s",word);
            if (line[0] == 'f') {
                find_instruction(&student, word, stu_cnt);
            } else if (line[0] == 's') {
                sort_instruction(&student, word, stu_cnt);
            } else if (line[0] == 'd') {
                delete_instruction(&student, word, stu_cnt);
            } else {
                puts("錯誤");
                return 0;
            }
        }


    }


    /* first file*/


}


char *get_word(char *t, char *w) {
    char *p = t;
    char *q = w;
    *w = '\0';

    while (*p && isspace(*p)) {
        p++;
    }
    while (*p && !isspace(*p)) {
        *q++ = *p++;
    }
    *q = '\0';
    if (*w == '\0') {
        return NULL;
    } else {
        return p;
    }
}

char *get_second_word(char *p, char *w) {
    for (int i = 0; i < 2; i++) {
        p = get_word(p, w);
    }
    return p;
}

void insert_instruction(File *student, char *p, char *w, int stu_cnt) {
    for (int i = 0; i < 5 && (p = get_word(p, w)) != NULL; i++) {
        if (i == NAME + 1) {
            strcpy(student->name[stu_cnt], w);
        } else if (i == EMAIL + 1) {
            strcpy(student->email[stu_cnt], w);
        } else if (i == URL + 1) {
            strcpy(student->url[stu_cnt], w);
        } else if (i == PHONE + 1) {
            strcpy(student->phone[stu_cnt], w);
        } else {
//                        printf("hi over");
        }
    }
}

void update_instruction(File *student, int target, char *p, char *w) {
//    puts("updating");
    for (int i = 2; i < 5 && (p = get_word(p, w)) != NULL; i++) {
//        printf("word:%s\n",w);
        if (i == EMAIL + 1 && strcmp(student->email[target], w) != 0) {
            strcpy(student->email[target], w);
        } else if (i == URL + 1 && strcmp(student->url[target], w) != 0) {
            strcpy(student->url[target], w);
        } else if (i == PHONE + 1 && strcmp(student->phone[target], w) != 0) {
            strcpy(student->phone[target], w);
        } else {
//           printf("hi over");
        }
    }
}

void find_instruction(File *output, char *w, int stu_cnt) {
    char temp[MAPEOPLE][32];
    int temp_cnt = 0;
    for (int i = 0; i < stu_cnt; i++) {
        if (strstr(output->name[i], w)) {
            strcpy(temp[temp_cnt++], output->name[i]);
        }
    }
//    printf("temp_cnt %d", temp_cnt);
    if (temp_cnt) {
        printf("Find %s result: ", w);
        for (int j = 0; j < temp_cnt; j++) {
            printf("%s ", temp[j]);
        }
        puts("");
    } else {
        printf("%s not found!\n", w);
    }

}

void print_instruction(File *output, int stu_cnt) {
    puts("number\tname\temail\tsite\tphone number");
    puts("----------------------------------------------------");
    int cnt = 1;
    for (int i = 0; i < stu_cnt; i++) {
        if (output->name[i][0] != '\0') {
            printf("[%d] %s\t%s\t%s\t%s\n", cnt, output->name[i], output->email[i], output->url[i], output->phone[i]);
            cnt++;
        }
    }
    puts("");
}

void delete_instruction(File *student, char *target, int stu_cnt) {
    for (int i = 0; i < stu_cnt; i++) {
        if (strcmp(student->name[i], target) == 0) {
            student->name[i][0] = '\0';
            student->email[i][0] = '\0';
            student->url[i][0] = '\0';
            student->phone[i][0] = '\0';
        }
    }
}

void sort_instruction(File *output, char *w, int stu_cnt) {
    if (strcmp(w, "n") == 0) {
        for (int i = 0; i < stu_cnt ; ++i) {
            for (int j = 0; j < i; j++) {
                if(strcmp(output->name[i],output->name[j])<0){
                    sort_copy(output,i,j);
                }
            }
        }
    } else if (strcmp(w, "e") == 0) {
        for (int i = 0; i < stu_cnt ; ++i) {
            for (int j = 0; j < i; j++) {
                if(strcmp(output->email[i],output->email[j])<0){
                    sort_copy(output,i,j);
                }
            }
        }
    } else if (strcmp(w, "u") == 0) {
        for (int i = 0; i < stu_cnt ; ++i) {
            for (int j = 0; j < i; j++) {
                if(strcmp(output->url[i],output->url[j])<0){
                    sort_copy(output,i,j);
                }
            }
        }
    } else if (strcmp(w, "p") == 0) {
        for (int i = 0; i < stu_cnt ; ++i) {
            for (int j = 0; j < i; j++) {
                if(atoi(output->phone[i])<atoi(output->phone[j])){
                    sort_copy(output,i,j);
                }
            }
        }
    }
}

void sort_copy(File *output,int i, int j){
    char *temp = malloc(256);
    strcpy(temp,output->name[i]);
    strcpy(output->name[i],output->name[j]);
    strcpy(output->name[j],temp);

    strcpy(temp,output->email[i]);
    strcpy(output->email[i],output->email[j]);
    strcpy(output->email[j],temp);

    strcpy(temp,output->url[i]);
    strcpy(output->url[i],output->url[j]);
    strcpy(output->url[j],temp);

    strcpy(temp,output->phone[i]);
    strcpy(output->phone[i],output->phone[j]);
    strcpy(output->phone[j],temp);
}
