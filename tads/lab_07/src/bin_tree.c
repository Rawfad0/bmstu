#include "bin_tree.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct
{
    char *key;
    int height;
} pair_t;

struct bintree
{
    pair_t data;
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
    tmp_node->data.key = tmp_key;
    tmp_node->data.height = 1;
    tmp_node->left = NULL;
    tmp_node->right = NULL;
    *node = tmp_node;
    return BIN_TREE_OK;
}


int get_height(bin_tree_t tree)
{
    if (tree == NULL)
        return 0;
    else
        return tree->data.height;
}

bt_rc_t calc_height(bin_tree_t tree)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;

    int left_height = get_height(tree->left);
    int right_height = get_height(tree->right);
    
    if (left_height > right_height)
        tree->data.height = left_height + 1;
    else
        tree->data.height = right_height + 1;
    return BIN_TREE_OK;
}

bin_tree_t avl_tree_rotate_right(bin_tree_t tree)
{
    bin_tree_t tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;

    calc_height(tree);
    calc_height(tmp);

    return tmp;
}

bin_tree_t avl_tree_rotate_left(bin_tree_t tree)
{
    bin_tree_t tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;

    calc_height(tree);
    calc_height(tmp);

    return tmp;
}

bin_tree_t avl_tree_node_balance(bin_tree_t tree)
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
            tree->left = avl_tree_rotate_left(tree->left);
        tree = avl_tree_rotate_right(tree);
    }
    if (left_height - right_height == -2)
    {
        // Высота правого поддерава выше левого на 2
        if (get_height(tree->right->left) > get_height(tree->right->right))
            tree->right = avl_tree_rotate_right(tree->right);
        tree = avl_tree_rotate_left(tree);
    }
    return tree; // Дерево сбалансировано
}

bt_rc_t avl_tree_insert(bin_tree_t *tree, const char *key)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;
    bt_rc_t rc;
    if (*tree == NULL)
        rc = bt_create_node(tree, (char *) key);
    else if (strcmp(key, (*tree)->data.key) < 0)
        rc = avl_tree_insert(&((*tree)->left), key);
    else if (strcmp(key, (*tree)->data.key) > 0)
        rc = avl_tree_insert(&((*tree)->right), key);
    else
        rc = BIN_TREE_OK;
    if (rc == BIN_TREE_OK)
        *tree = avl_tree_node_balance(*tree);
    return rc;
}

typedef struct
{
    bin_tree_t *tree;
    bt_rc_t rc;
} avl_struct_t;

void avl_func(const char *key, int *value, void *n)
{
    if (key == NULL || value == NULL)
        return;

    avl_struct_t *avl = n;
    avl->rc = avl_tree_insert(avl->tree, key);
}

bt_rc_t bst_to_avl_tree(bin_tree_t *tree)
{
    bin_tree_t avl_tree = NULL;
    avl_struct_t avl = { &avl_tree, BIN_TREE_OK };
    bin_tree_each(*tree, (*avl_func), &avl);
    if (avl.rc != BIN_TREE_OK)
        return avl.rc;
    bin_tree_clear(tree);
    *tree = *avl.tree;
    return avl.rc;
}

bt_rc_t bt_find_node(const bin_tree_t *tree, const char *key, bin_tree_t *tree_node, int *cmp_count)
{
    if (*tree == NULL)
        return BIN_TREE_NOT_FOUND;
    else if ((*cmp_count)++, strcmp(key, (*tree)->data.key) == 0)
    {
        *tree_node = *tree;
        return BIN_TREE_OK;
    }
    else if (strcmp(key, (*tree)->data.key) < 0)
        return bt_find_node(&((*tree)->left), key, tree_node, cmp_count);
    else if (strcmp(key, (*tree)->data.key) > 0)
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
        
        free((*tree)->data.key);
        free(*tree);
        *tree = NULL;
    }
}

bt_rc_t bin_tree_insert(bin_tree_t *tree, const char *key)
{
    if (*tree == NULL)
        return bt_create_node(tree, (char *) key);
    else if (strcmp(key, (*tree)->data.key) < 0)
        return bin_tree_insert(&((*tree)->left), key);
    else if (strcmp(key, (*tree)->data.key) > 0)
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

bt_rc_t bin_tree_remove(bin_tree_t *tree, char *key)
{
    if (tree == NULL)
        return BIN_TREE_INVALID_PARAM;
    bt_rc_t rc = BIN_TREE_OK;
    if (*tree == NULL)
        rc = BIN_TREE_NOT_FOUND;
    else if (strcmp(key, (*tree)->data.key) < 0)
        rc = bin_tree_remove(&((*tree)->left), key);
    else if (strcmp(key, (*tree)->data.key) > 0)
        rc = bin_tree_remove(&((*tree)->right), key);
    else
    {
        if ((*tree)->left == NULL && (*tree)->right == NULL)
            free((*tree)->data.key), free(*tree), *tree = NULL;
        else if ((*tree)->left != NULL && (*tree)->right == NULL)
        {
            bin_tree_t tmp = (*tree)->left;
            free((*tree)->data.key);
            free(*tree);
            *tree = tmp;
        }
        else if ((*tree)->left == NULL && (*tree)->right != NULL)
        {
            bin_tree_t tmp = (*tree)->right;
            free((*tree)->data.key);
            free(*tree);
            *tree = tmp;
        }
        else
        {
            bin_tree_t *node = &((*tree)->left);
            // Ищем указатель на указатель на самый правый в левом поддереве
            for (; (*node)->right != NULL; node = &((*node)->right));
            free((*tree)->data.key);        // Очистка ключа перед заменой данных узла
            (*tree)->data = (*node)->data;  // Замена данных на новые
            free(*node);                    // Очистка найденной вершины
            *node = NULL;                   // Удаление найденной вершины из дерева
        }
    }
    return rc;
}

// Обход префиксным способом
void bin_tree_each(const bin_tree_t tree, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (tree != NULL)
    {
        (*action)(tree->data.key, &tree->data.height, param);
        
        bin_tree_each(tree->left, action, param);
        bin_tree_each(tree->right, action, param);
    }
    else
        (*action)(NULL, NULL, param);
}

void bin_tree_print(bin_tree_t tree, FILE *f)
{
    if (tree != NULL)
    {
        fprintf(f, "\t%s;\n", tree->data.key);
        if (tree->left != NULL)
            fprintf(f, "\t%s -- %s;\n", tree->data.key, tree->left->data.key);
        if (tree->right != NULL)
            fprintf(f, "\t%s -- %s;\n", tree->data.key, tree->right->data.key);
        
        bin_tree_print(tree->left, f);
        bin_tree_print(tree->right, f);
    }
}
