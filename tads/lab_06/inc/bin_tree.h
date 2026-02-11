/**
 * @file bin_tree.h
 * @brief Частотный словарь на двоичном дереве поиска
 * 
 */

#ifndef BIN_TREE_H__
#define BIN_TREE_H__

typedef enum error
{
    /// При выполнении действия ошибок не возникло
    BIN_TREE_OK = 0,
    /// При вызове функции указаны неверные параметры
    BIN_TREE_INVALID_PARAM, 
    /// При выполнении действия возникли ошибки при работе с памятью 
    BIN_TREE_MEM,
    /// Не найдено значение по указанному ключу
    BIN_TREE_NOT_FOUND
} bt_rc_t;

typedef struct bintree *bin_tree_t;

void bin_tree_clear(bin_tree_t *tree);

bt_rc_t bin_tree_insert(bin_tree_t *tree, const char *key);

bt_rc_t bin_tree_find(const bin_tree_t tree, const char *key, int **num, int *cmp_count);

bt_rc_t bin_tree_remove(bin_tree_t *tree, const char **key);

void bin_tree_each(const bin_tree_t tree, void (*action)(const char *key, int *num, void *param), void *param);

#endif
