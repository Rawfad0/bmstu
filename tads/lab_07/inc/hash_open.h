/**
 * @file hash.h
 * @brief Хеш-таблица
 * 
 */

#ifndef OPEN_HASH_H__
#define OPEN_HASH_H__

#include "hash.h"

typedef struct hash_table_open *hto_t;

hto_t hto_create(void);

void hto_destroy(hto_t *table);

ht_rc_t hto_clear(hto_t table);

ht_rc_t hto_insert(hto_t *table, const char *key, size_t c2restr);

ht_rc_t hto_find(hto_t table, const char *key, int *cmp_count);

ht_rc_t hto_remove(hto_t table, char *key);

void hto_print(hto_t table);

ht_rc_t hto_restruct(hto_t *table, size_t c2restr);

size_t get_hto_table_size(hto_t table);

size_t hto_count(hto_t table);

#endif