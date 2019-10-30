#include <stdio.h>

#define MAX_WORD_LEN 64

typedef struct word_hash_node{
    char word[MAX_WORD_LEN];
    struct word_hash_node *next;
} word_hash_node_t;

typedef struct word_hash_tbl{
    word_hash_node_t **head;
    int bucket_size;
} word_hash_tbl_t;

word_hash_tbl_t *word_hash_init(int bucket_size)
{
    word_hash_tbl_t *tbl;
    tbl = (word_hash_tbl_t*)malloc(sizeof(word_hash_tbl_t));

    if (tbl == NULL) {
        return NULL;
    }

    tbl->bucket_size = bucket_size;
    tbl->head = (word_hash_node_t*)malloc(sizeof(word_hash_node_t) * bucket_size);
    if (tbl->head == NULL) {
        free(tbl);
        return NULL;
    }

    for (int i = 0; i < bucket_size; i++) {
        tbl->head[i] = NULL;
    }

    return tbl;
}

/* learn from https://blog.csdn.net/matrix_designer/article/details/6462284 */
int word_get_hash_index(const char* word, int len)
{
    int sum = 0;
    int h = 0;
    char *p = word;

    while(p - word < len){
        short a = *(p++)
        sum ^= a * (p - word);
        h ^= a / (p - word);
    }

    return ((sum << 16) | h) % MAX_PRIME_LESS_THAN_BUCKET_SIZE;
}
