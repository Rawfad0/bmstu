/**
 * @file avl_tree.h
 * @brief Частотный словарь на сбалансированном двоичном дереве поиска
 * 
 */

#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include "rc_tree.h"

typedef struct avltree *avl_tree_t;

void avl_tree_clear(avl_tree_t *tree);

bt_rc_t avl_tree_insert(avl_tree_t *tree, const char *key);

bt_rc_t avl_tree_find(const avl_tree_t tree, const char *key, int *cmp_count);

bt_rc_t avl_tree_remove(avl_tree_t *tree, const char **key);

avl_tree_t avl_tree_node_balance(avl_tree_t tree);

void avl_tree_each(const avl_tree_t tree, void (*action)(const char *key, void *param), void *param);

#endif
