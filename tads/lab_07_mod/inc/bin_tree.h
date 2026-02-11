/**
 * @file bin_tree.h
 * @brief Частотный словарь на двоичном дереве поиска
 * 
 */

#ifndef BIN_TREE_H__
#define BIN_TREE_H__

#include "rc_tree.h"

typedef struct bintree *bin_tree_t;

void bin_tree_clear(bin_tree_t *tree);

bt_rc_t bin_tree_insert(bin_tree_t *tree, const char *key);

bt_rc_t bin_tree_find(const bin_tree_t tree, const char *key, int *cmp_count);

bt_rc_t bin_tree_remove(bin_tree_t *tree, const char **key);

void bin_tree_each(const bin_tree_t tree, void (*action)(const char *key, void *param), void *param);

#endif
