#include "avl_tree.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <stdio.h>


struct avltree
{
    char *data;
    int height;
    avl_tree_t left;
    avl_tree_t right;
};

bt_rc_t avlt_create_node(avl_tree_t *node, char *key)
{
    avl_tree_t tmp_node = malloc(sizeof(struct avltree));
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
    tmp_node->height = 1;
    tmp_node->left = NULL;
    tmp_node->right = NULL;
    *node = tmp_node;
    return BIN_TREE_OK;
}

int get_height(avl_tree_t tree)
{
    if (tree == NULL)
        return 0;
    else
        return tree->height;
}

bt_rc_t calc_height(avl_tree_t tree)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;

    int left_height = get_height(tree->left);
    int right_height = get_height(tree->right);
    
    if (left_height > right_height)
        tree->height = left_height + 1;
    else
        tree->height = right_height + 1;
    return BIN_TREE_OK;
}

avl_tree_t alv_tree_rotate_right(avl_tree_t tree)
{
    avl_tree_t tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;

    calc_height(tree);
    calc_height(tmp);

    return tmp;
}

avl_tree_t alv_tree_rotate_left(avl_tree_t tree)
{
    avl_tree_t tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;

    calc_height(tree);
    calc_height(tmp);

    return tmp;
}

avl_tree_t avl_tree_node_balance(avl_tree_t tree)
{
    if (tree == NULL)
        return tree;
    calc_height(tree);

    int left_height = get_height(tree->left);
    int right_height = get_height(tree->right);

    if (left_height - right_height == 2)
    {
        // Высота левого поддерава выше правого на 2
        if (get_height(tree->left->left) < get_height(tree->left->right))
            tree->left = alv_tree_rotate_left(tree->left);
        tree = alv_tree_rotate_right(tree);
    }
    if (left_height - right_height == -2)
    {
        // Высота правого поддерава выше левого на 2
        if (get_height(tree->right->left) > get_height(tree->right->right))
            tree->right = alv_tree_rotate_right(tree->right);
        tree = alv_tree_rotate_left(tree);
    }
    return tree; // Дерево сбалансировано
}

bt_rc_t avlt_find_node(const avl_tree_t *tree, const char *key, avl_tree_t *tree_node, int *cmp_count)
{
    if (*tree == NULL)
        return BIN_TREE_NOT_FOUND;
    else if ((*cmp_count)++, strcmp(key, (*tree)->data) == 0)
    {
        *tree_node = *tree;
        return BIN_TREE_OK;
    }
    else if (strcmp(key, (*tree)->data) < 0)
        return avlt_find_node(&((*tree)->left), key, tree_node, cmp_count);
    else if (strcmp(key, (*tree)->data) > 0)
        return avlt_find_node(&((*tree)->right), key, tree_node, cmp_count);
    else
        return BIN_TREE_NOT_FOUND;
}

void avl_tree_clear(avl_tree_t *tree)
{
    if (*tree != NULL)
    {
        avl_tree_clear(&((*tree)->left));
        avl_tree_clear(&((*tree)->right));
        
        free((*tree)->data);
        free(*tree);
        *tree = NULL;
    }
}

bt_rc_t avl_tree_insert(avl_tree_t *tree, const char *key)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;
    bt_rc_t rc;
    if (*tree == NULL)
        rc = avlt_create_node(tree, (char *) key);
    else if (strcmp(key, (*tree)->data) < 0)
        rc = avl_tree_insert(&((*tree)->left), key);
    else if (strcmp(key, (*tree)->data) > 0)
        rc = avl_tree_insert(&((*tree)->right), key);
    else
        rc = BIN_TREE_OK;
    if (rc == BIN_TREE_OK)
        *tree = avl_tree_node_balance(*tree);
    return rc;
}

bt_rc_t avl_tree_find(const avl_tree_t tree, const char *key, int *cmp_count)
{
    avl_tree_t node = NULL;
    bt_rc_t rc = avlt_find_node(&tree, key, &node, cmp_count);
    return rc;
}

bt_rc_t avl_tree_remove(avl_tree_t *tree, const char **key)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;
    bt_rc_t rc = BIN_TREE_OK;;
    if (*tree == NULL)
        rc = BIN_TREE_NOT_FOUND;
    else if (strcmp(*key, (*tree)->data) < 0)
        rc = avl_tree_remove(&((*tree)->left), key);
    else if (strcmp(*key, (*tree)->data) > 0)
        rc = avl_tree_remove(&((*tree)->right), key);
    else
    {
        *key = (*tree)->data;    // Возврат ключа удаляемой вершины
        if ((*tree)->left == NULL && (*tree)->right == NULL)
            free(*tree), *tree = NULL;
        else if ((*tree)->left != NULL && (*tree)->right == NULL)
        {
            avl_tree_t tmp = (*tree)->left;
            free(*tree);
            *tree = tmp;
        }
        else if ((*tree)->left == NULL && (*tree)->right != NULL)
        {
            avl_tree_t tmp = (*tree)->right;
            free(*tree);
            *tree = tmp;
        }
        else
        {
            avl_tree_t *node = &((*tree)->left);
            // Ищем указатель на указатель на самый правый в левом поддереве
            for (; (*node)->right != NULL; node = &((*node)->right));
            free((*tree)->data);        // Очистка ключа перед заменой данных узла
            (*tree)->data = (*node)->data;  // Замена данных на новые
            free(*node);                    // Очистка найденной вершины
            *node = NULL;                   // Удаление найденной вершины из дерева
        }
    }
    if (rc == BIN_TREE_OK)
        *tree = avl_tree_node_balance(*tree);
    return rc;
}

// Обход префиксным способом
void avl_tree_each(const avl_tree_t tree, void (*action)(const char *key, void *param), void *param)
{
    if (tree != NULL)
    {
        (*action)(tree->data, param);
        
        avl_tree_each(tree->left, action, param);
        avl_tree_each(tree->right, action, param);
    }
    else
        (*action)(NULL, param);
}
