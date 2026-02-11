/**
 * @file hash.h
 * @brief Хеш-таблица
 * 
 */

#ifndef CLOSED_HASH_H__
#define CLOSED_HASH_H__

#include "hash.h"

typedef struct hash_table_closed *htc_t;

htc_t htc_create(void);

void htc_destroy(htc_t *table);

ht_rc_t htc_clear(htc_t table);

ht_rc_t htc_insert(htc_t *table, const char *key, size_t c2restr);

ht_rc_t htc_find(htc_t table, const char *key, int *cmp_count, size_t c2restr);

ht_rc_t htc_remove(htc_t table, char *key, size_t c2restr);

void htc_print(htc_t table);

ht_rc_t htc_restruct(htc_t *table, size_t c2restr);

size_t get_htc_table_size(htc_t table);

size_t htc_count(htc_t table);

#endif