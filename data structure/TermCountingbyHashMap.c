/*利用 HashMap (HashTable) 統計詞頻*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUF_SIZE 1024
#define MAP_CAP_BITS 5

/* ============ 型別定義 ============ */

typedef struct entry {
    char *key;
    int value;
    struct entry *next;
} Entry;


/* Hash Map (i.e., Hash Table) */
typedef struct {
    Entry *buckets;
    size_t capacity; // 桶子數 (i.e., 表格列數)
    size_t size; // 已插入的條目數 (初始為 0)
} HashMap;


int map_init(HashMap *map, unsigned int cap_bits);

int map_entries(HashMap *map, Entry ***entries);

int entry_cmp(const void *a, const void *b);


size_t my_hash_function(const char *key);


size_t map_idx(HashMap *map, const char *key);


int map_put(HashMap *map, const char *key, int value);


int *map_get(HashMap *map, const char *key);


void map_destroy(HashMap *map);

int main() {
    /* =================== INITIALIZE =================== */
    HashMap map;
    if (map_init(&map, MAP_CAP_BITS) < 0)
        fprintf(stderr, "map_init error\n");

    /* ================== INPUT TERMS =================== */
    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, stdin)) {
        /* 去除輸入後方「可能」的換行字元 */
        buf[strcspn(buf, "\r\n")] = '\0';


        /* 目前是否欲對 term 作遞減 */
        const _Bool decrease = (*buf == '-');

        char *term;
        int increment; // 增量值

        if (decrease) {
            term = buf + 1;
            increment = -1;
        } else {
            term = buf;
            increment = 1;
        }
        /* 根據 term 取得對應的值「位址」 */
        int *value = map_get(&map, term);
        if (value) {
            (*value) += increment;
        }// 根據增量值，修改 term count
        else if (!decrease) {
            map.size++;
            map_put(&map, term, 1);
        }// 若未插入過該 term，且不為遞減模式


    }

    /* =============== OUTPUT TERM COUNT ================ */
    {
        const size_t size = map.size;
        Entry **entries;
        if (map_entries(&map, &entries) < 0) // 取得所有條目
            fprintf(stderr, "map_entries error\n");

        /* 根據 entry_cmp 排序*/
        qsort(entries, size, sizeof(Entry *), entry_cmp);


        /* 按照排序結果依序輸出*/

        for (size_t i = 0; i < size; i++) {

            Entry *e = entries[i];
            const char *term = e->key;
            const int count = e->value;
            printf("%d %s\n", count, term);
        }

        /* 釋放條目指標空間 */
        free(entries);
    }

    /* =================== TERMINATE ==================== */
    map_destroy(&map);
}

int map_init(HashMap *map, unsigned int cap_bits) {
    const size_t capacity = 1u << cap_bits; // 計算 2 的 cap_bts 次方
    map->buckets = calloc(capacity, sizeof(Entry)); // 分配「全為 0」的空間
    map->capacity = capacity;
    map->size = 0;

    return -(map->buckets == NULL);
}

int map_entries(HashMap *map, Entry ***entries) {
    Entry *table = map->buckets;
    const size_t capacity = map->capacity;
    size_t size = map->size;

    /* 若目前雜湊表無任何元素，則回傳 0 */
    if (!size) {
        *entries = NULL;
        return 0;
    }

    /* 否則，根據目前元素數量分配空間 */
    Entry **ret = malloc(size * sizeof(Entry *));
    if (!ret)
        return -1; // 分配失敗則傳回 -1

    size_t j = 0;
    for (size_t i = 0; size && i < capacity; i++) {
        Entry *e = table + i;
        if (!e->key)
            continue; // 若目前 bucket 為空，則查找下一個 bucket

        while (e) {
            ret[j++] = e; // 添加目前的 entry
            size--;
            e = e->next; // 查找鏈結串列節點之 entry
        }
    }

    *entries = ret;
    return 0;
}

int entry_cmp(const void *a, const void *b) {
    return (*(Entry **) a)->value == (*(Entry **) b)->value ? (strcmp((*(Entry **) a)->key, (*(Entry **) b)->key)) :
           (*(Entry **) b)->value - (*(Entry **) a)->value;

}

int *map_get(HashMap *map, const char *key) {
    int idx = map_idx(map, key);   //桶子為空
    if (!map->buckets[idx].key) {
        return NULL;
    } else {
        if (strcmp(map->buckets[idx].key, key) == 0) {
            return &map->buckets[idx].value;
        }
        Entry **p = &map->buckets[idx].next;
        Entry *e;
        while ((e = *p)) {
            if (strcmp(e->key, key) == 0) {

                return &e->value;
            }
            p = &e->next;
        }
    }
    return NULL;
}


int map_put(HashMap *map, const char *key, int value) {
    int idx = map_idx(map, key);
    Entry *e = &map->buckets[idx];
    if (!e->key){
        e->key = strdup(key);
        e->value = value;
        return 1;
    }
    while (e->key){
        if(strcmp(e->key,key)==0){
            puts("error");
            return -1;
        }
        if(e->next){
            e = e->next;
        } else{
            break;
        }
    }
    e->next = malloc(sizeof(Entry));
    e = e->next;
    e->key = strdup(key);
    e->value = value;
    e->next = NULL;
    return 1;
}

size_t my_hash_function(const char *key) {
    size_t hash_val = 5381;
    int c;
    while ((c = *key++))
        hash_val = ((hash_val << 5u) + hash_val) + c;

    return hash_val;
}

/**
* map_idx - 根據 key 計算雜湊值，並回傳用於雜湊表的索引值 (Index)，
*           (i.e., 第 i 個桶子 = 表格的第 i 列)
*
*           hint:
*           內部應呼叫 my_hash_function
*
* @map: 欲操作之 HashMap
* @key: 鍵
* @return 根據 `key` 所計算出的雜湊表索引 (Index)
*/
size_t map_idx(HashMap *map, const char *key) {
    int val = my_hash_function(key);
    val = val % map->capacity;
    return val;
}

/**
 * map_destroy - 釋放 HashMap 所有相關資源，包含：
 *               @ 接在桶子後方的鏈結串列之節點
 *               @ 每個條目的 key
 *               @ 整張雜湊表
 *
 * @map: 欲操作之 HashMap
 */
void map_destroy(HashMap *map) {
    for (int i = 0; i < 32; i++) {
        if (!map->buckets[i].next) {
            free(map->buckets[i].key);
        }
        Entry **p = &map->buckets[i].next;
        Entry *e;
        while ((e = *p)) {
            Entry *tem = e->next;
            free(e);
            p = &tem;
        }

    }
}