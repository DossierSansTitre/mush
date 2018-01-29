#include <stdlib.h>
#include <string.h>
#include <hash_table.h>

static uint32_t hash(const char* str)
{
    uint32_t h;
    size_t i;
    uint8_t c;

    h = 0x811c9dc5;
    i = 0;

    for (;;)
    {
        c = str[i];
        if (c == 0)
            break;
        h ^= c;
        h *= 16777619;
        i++;
    }
    return h;
}

static size_t internal_lookup(const hash_table* ht, const char* str)
{
    size_t h;
    const hash_table_bucket* bucket;

    h = hash(str);
    for (;;)
    {
        h &= (ht->buckets_capacity - 1);
        bucket = ht->buckets + h;
        if (bucket->string_index == 0)
            return h;
        if (strcmp(str, ht->string_table[bucket->string_index - 1]) == 0)
            return h;
        h++;
    }
}

void hash_table_init(hash_table* ht)
{
    ht->string_table_size = 0;
    ht->string_table_capacity = 256;
    ht->string_table = malloc(sizeof(char*) * ht->string_table_capacity);
    ht->buckets_size = 0;
    ht->buckets_capacity = 256;
    ht->buckets = malloc(sizeof(hash_table_bucket) * ht->buckets_capacity);
    memset(ht->buckets, 0, sizeof(hash_table_bucket) * ht->buckets_capacity);
}

void hash_table_destroy(hash_table* ht)
{
    free(ht->string_table);
    free(ht->buckets);
}


int hash_table_lookup(const hash_table* t, const char* str, uint32_t* out)
{
    size_t index;
    const hash_table_bucket* bucket;

    index = internal_lookup(t, str);
    bucket = t->buckets + index;
    if (bucket->string_index == 0)
        return 0;
    *out = bucket->value;
    return 1;
}

void hash_table_insert(hash_table* t, const char* str, uint32_t value)
{
    size_t new_str_len;
    char* new_str;
    size_t new_str_index;
    size_t bucket_index;
    hash_table_bucket* bucket;

    bucket_index = internal_lookup(t, str);
    bucket = t->buckets + bucket_index;
    if (bucket->string_index == 0)
    {
        /* This is a new entry */
        new_str_len = strlen(str);
        new_str = malloc(new_str_len + 1);
        strcpy(new_str, str);
        new_str_index = t->string_table_size;
        t->string_table_size++;
        t->string_table[new_str_index] = new_str;
        bucket->value = value;
        t->buckets_size++;
    }
    else
    {
        bucket->value = value;
    }
}
