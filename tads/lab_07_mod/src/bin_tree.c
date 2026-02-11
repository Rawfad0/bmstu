#include "bin_tree.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <stdio.h>


struct bintree
{
    char *data;
    bin_tree_t left;
    bin_tree_t right;
};

bt_rc_t bt_create_node(bin_tree_t *node, char *key)
{
    bin_tree_t tmp_node = malloc(sizeof(struct bintree));
    if (tmp_node == NULL)
        return BIN_TREE_MEM;
    char *tmp_key = malloc(sizeof(char)*(strlen(key) + 1));
    if (tmp_key == NULL)
    {
        free(tmp_node);
        return BIN_TREE_MEM;
    }

    strcpy(tmp_key, key);
    tmp_node->data = tmp_key;
    tmp_node->left = NULL;
    tmp_node->right = NULL;
    *node = tmp_node;
    return BIN_TREE_OK;
}

bt_rc_t bt_find_node(const bin_tree_t *tree, const char *key, bin_tree_t *tree_node, int *cmp_count)
{
    if (*tree == NULL)
        return BIN_TREE_NOT_FOUND;
    else if ((*cmp_count)++, strcmp(key, (*tree)->data) == 0)
    {
        *tree_node = *tree;
        return BIN_TREE_OK;
    }
    else if (strcmp(key, (*tree)->data) < 0)
        return bt_find_node(&((*tree)->left), key, tree_node, cmp_count);
    else if (strcmp(key, (*tree)->data) > 0)
        return bt_find_node(&((*tree)->right), key, tree_node, cmp_count);
    else
        return BIN_TREE_NOT_FOUND;
}

void bin_tree_clear(bin_tree_t *tree)
{
    if (*tree != NULL)
    {
        bin_tree_clear(&((*tree)->left));
        bin_tree_clear(&((*tree)->right));
        
        free((*tree)->data);
        free(*tree);
        *tree = NULL;
    }
}

bt_rc_t bin_tree_insert(bin_tree_t *tree, const char *key)
{
    if (*tree == NULL)
        return bt_create_node(tree, (char *) key);
    else if (strcmp(key, (*tree)->data) < 0)
        return bin_tree_insert(&((*tree)->left), key);
    else if (strcmp(key, (*tree)->data) > 0)
        return bin_tree_insert(&((*tree)->right), key);
    else
        return BIN_TREE_OK;
}

bt_rc_t bin_tree_find(const bin_tree_t tree, const char *key, int *cmp_count)
{
    bin_tree_t node = NULL;
    bt_rc_t rc = bt_find_node(&tree, key, &node, cmp_count);
    return rc;
}

bt_rc_t bin_tree_remove(bin_tree_t *tree, const char **key)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;
    
    bt_rc_t rc = BIN_TREE_OK;
    *key = (*tree)->data;    // Возврат ключа удаляемой вершины
    if ((*tree)->left == NULL && (*tree)->right == NULL)
        free(*tree), *tree = NULL;
    else if ((*tree)->left != NULL && (*tree)->right == NULL)
    {
        bin_tree_t tmp = (*tree)->left;
        free(*tree);
        *tree = tmp;
    }
    else if ((*tree)->left == NULL && (*tree)->right != NULL)
    {
        bin_tree_t tmp = (*tree)->right;
        free(*tree);
        *tree = tmp;
    }
    else
    {
        bin_tree_t *node = &((*tree)->left);
        // Ищем указатель на указатель на самый правый в левом поддереве
        for (; (*node)->right != NULL; node = &((*node)->right));
        free((*tree)->data);            // Очистка ключа перед заменой данных узла
        (*tree)->data = (*node)->data;  // Замена данных на новые
        free(*node);                    // Очистка найденной вершины
        *node = NULL;                   // Удаление найденной вершины из дерева
    }
    return rc;
}

// Обход префиксным способом
void bin_tree_each(const bin_tree_t tree, void (*action)(const char *key, void *param), void *param)
{
    if (tree != NULL)
    {
        (*action)(tree->data, param);
        
        bin_tree_each(tree->left, action, param);
        bin_tree_each(tree->right, action, param);
    }
    else
        (*action)(NULL, param);
}
