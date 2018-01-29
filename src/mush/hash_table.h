#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>

struct hash_table_bucket_
{
    uint32_t    string_index;
    uint32_t    value;
};
typedef struct hash_table_bucket_ hash_table_bucket;

struct hash_table_
{
    char**              string_table;
    size_t              string_table_size;
    size_t              string_table_capacity;
    hash_table_bucket*  buckets;
    size_t              buckets_size;
    size_t              buckets_capacity;
};
typedef struct hash_table_ hash_table;

void    hash_table_init(hash_table* ht);
void    hash_table_destroy(hash_table* ht);
int     hash_table_lookup(const hash_table* t, const char* str, uint32_t* out);
void    hash_table_insert(hash_table* t, const char* str, uint32_t value);

#endif
