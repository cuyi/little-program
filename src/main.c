#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PICE_SIZE 1024 * 1024 // 1M bytes

int main(void)
{
    // open file
    FILE *file = fopen("local_test.txt", "r");
    if (file == NULL) {
        return 1;
    }

    if (fseek(file, 0L, SEEK_END) == -1) {
        return 1;
    }

    long file_size = ftell(file);
    if (file_size == -1) {
        return 1;
    }

    // read file
    int times = (file_size + PICE_SIZE) / PICE_SIZE;
    char *tmp_buf = (char*)malloc(PICE_SIZE);
    if (tmp_buf == NULL) {
        return 1;
    }

    for (int i = 0; i < times; i++) {
        memset(tmp_buf, PICE_SIZE);

        size_t size_read = fread(tmp_buf, 1, PICE_SIZE, file);
        if (size_read <= 0){
            free(tmp_buf);
            return 1;
        }

        //solve the read bytes
        word_statistic_by_hash(tmp_buf, PICE_SIZE);
    }

    free(tmp_buf);



    return 0;
}




#define MAX_WORD_LEN 64
void word_statistic_by_hash(char *buf, size_t buf_size)
{
    char word[MAX_WORD_LEN] = {0};
    int word_len = 0;

    int offset = 0;
    while(offset < buf_size) {
        offset = get_one_word(word, word_len, buf + offset, buf_size);

        int hash_idx = word_get_hash_index(word, word_len);
        word_insert_hash_index(hash_idx); // 需要解决冲突

        //需要处理结束边界 不够一个单词，需要保留其信息
    }
}
