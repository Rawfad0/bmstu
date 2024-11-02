#include "associative_array.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef enum bt_error
{
    // При выполнении действия ошибок не возникло
    BIN_TREE_OK = 0,
    // При вызове функции указаны неверные параметры
    BIN_TREE_INVALID_PARAM, 
    // При выполнении действия возникли ошибки при работе с памятью 
    BIN_TREE_MEM,
    // Не найдено значение по указанному ключу
    BIN_TREE_NOT_FOUND,
    // Значение с таким ключом уже в дереве
    BIN_TREE_KEY_EXISTS
} bt_rc_t;

typedef struct
{
    char *key;
    int value;
} pair_t;

typedef struct avltree *avl_tree_t;
struct avltree
{
    pair_t data;
    int height;
    avl_tree_t left;
    avl_tree_t right;
};

bt_rc_t avlt_create_node(avl_tree_t *node, char *key, int num)
{
    bt_rc_t rc = BIN_TREE_OK;
    avl_tree_t tmp_node;
    char *tmp_key;
    if ((tmp_node = malloc(sizeof(struct avltree))) == NULL)
        rc = BIN_TREE_MEM;
    else if ((tmp_key = malloc(sizeof(char)*(strlen(key) + 1))) == NULL)
        free(tmp_node), rc = BIN_TREE_MEM;
    else
    {
        strcpy(tmp_key, key);
        tmp_node->data.key = tmp_key;
        tmp_node->data.value = num;
        tmp_node->height = 1;
        tmp_node->left = NULL;
        tmp_node->right = NULL;
        *node = tmp_node;
    }
    return rc;
}

int get_height(avl_tree_t tree)
{
    if (tree == NULL)
        return 0;
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
        if (get_height(tree->left->left) < get_height(tree->left->right))
            tree->left = alv_tree_rotate_left(tree->left);
        tree = alv_tree_rotate_right(tree);
    }
    if (left_height - right_height == -2)
    {
        if (get_height(tree->right->left) > get_height(tree->right->right))
            tree->right = alv_tree_rotate_right(tree->right);
        tree = alv_tree_rotate_left(tree);
    }
    return tree;
}

void free_node(avl_tree_t *tree)
{
    free((*tree)->data.key);
    free(*tree);
}

void avl_tree_clear(avl_tree_t *tree)
{
    if (*tree != NULL)
    {
        avl_tree_clear(&((*tree)->left));
        avl_tree_clear(&((*tree)->right));
        free_node(tree);
        *tree = NULL;
    }
}

bt_rc_t avl_tree_insert(avl_tree_t *tree, const char *key, int num)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;
    bt_rc_t rc;
    if (*tree == NULL)
        rc = avlt_create_node(tree, (char *) key, num);
    else if (strcmp(key, (*tree)->data.key) < 0)
        rc = avl_tree_insert(&((*tree)->left), key, num);
    else if (strcmp(key, (*tree)->data.key) > 0)
        rc = avl_tree_insert(&((*tree)->right), key, num);
    else
        rc = BIN_TREE_KEY_EXISTS;
    if (rc == BIN_TREE_OK)
        *tree = avl_tree_node_balance(*tree);
    return rc;
}

bt_rc_t avl_tree_find(const avl_tree_t tree, const char *key, int **num)
{
    if (tree == NULL)
        return BIN_TREE_NOT_FOUND;
    bt_rc_t rc = BIN_TREE_OK;
    if (strcmp(key, tree->data.key) == 0)
        *num = &tree->data.value, rc = BIN_TREE_OK;
    else if (strcmp(key, tree->data.key) < 0)
        rc = avl_tree_find(tree->left, key, num);
    else if (strcmp(key, tree->data.key) > 0)
        rc = avl_tree_find(tree->right, key, num);
    return rc;
}

bt_rc_t avl_tree_remove(avl_tree_t *tree, const char *key)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;
    bt_rc_t rc = BIN_TREE_OK;;
    if (*tree == NULL)
        rc = BIN_TREE_NOT_FOUND;
    else if (strcmp(key, (*tree)->data.key) < 0)
        rc = avl_tree_remove(&((*tree)->left), key);
    else if (strcmp(key, (*tree)->data.key) > 0)
        rc = avl_tree_remove(&((*tree)->right), key);
    else
    {
        if ((*tree)->left == NULL && (*tree)->right == NULL)
        {
            free_node(tree);
            *tree = NULL;
        }
        else if ((*tree)->left != NULL && (*tree)->right == NULL)
        {
            avl_tree_t tmp = (*tree)->left;
            free_node(tree);
            *tree = tmp;
        }
        else if ((*tree)->left == NULL && (*tree)->right != NULL)
        {
            avl_tree_t tmp = (*tree)->right;
            free_node(tree);
            *tree = tmp;
        }
        else
        {
            avl_tree_t *node = &((*tree)->left);
            for (; (*node)->right != NULL; node = &((*node)->right));
            free((*tree)->data.key);
            (*tree)->data = (*node)->data;
            avl_tree_t tmp = (*node)->left;
            free(*node);
            *node = tmp;
        }
    }
    if (rc == BIN_TREE_OK)
        *tree = avl_tree_node_balance(*tree);
    return rc;
}

// Обход префиксным способом
void avl_tree_each(const avl_tree_t tree, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (tree == NULL)
        return;
    (*action)(tree->data.key, &tree->data.value, param);
    avl_tree_each(tree->left, action, param);
    avl_tree_each(tree->right, action, param);
}

// Реализация на основе АВЛ-дерева
struct assoc_array_type
{
    avl_tree_t tree;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t assoc_arr = malloc(sizeof(struct assoc_array_type));
    if (assoc_arr != NULL)
        assoc_arr->tree = NULL;
    return assoc_arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL);
    else
    {
        assoc_array_clear(*arr);
        free(*arr);
        *arr = NULL;
    }
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || key == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (strcmp(key, "") == 0)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
        rc = (assoc_array_error_t) avl_tree_insert(&arr->tree, key, num);
    return rc;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || num == NULL || key == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (strcmp(key, "") == 0)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
        rc = (assoc_array_error_t) avl_tree_find(arr->tree, key, num);
    return rc;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (strcmp(key, "") == 0)
        rc = ASSOC_ARRAY_INVALID_PARAM;
    else
        rc = (assoc_array_error_t) avl_tree_remove(&arr->tree, key);
    return rc;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    avl_tree_clear(&arr->tree);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || (*action) == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    avl_tree_each(arr->tree, (*action), param);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr->tree == NULL)
        rc = ASSOC_ARRAY_NOT_FOUND;
    else
    {
        avl_tree_t node = arr->tree;
        for (; node->left != NULL; node = node->left);
        *num = &node->data.value;
    }
    return rc;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr->tree == NULL)
        rc = ASSOC_ARRAY_NOT_FOUND;
    else
    {
        avl_tree_t node = arr->tree;
        for (; node->right != NULL; node = node->right);
        *num = &node->data.value;
    }
    return rc;
}
