#include "hash_open.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define START_N 11 // Начальная длина хеш-таблицы
#define COEF 2      // Увеличение в COEF раз при недопустимой коллизии
#define K 29        // k многочлена больше количества букв алфавита
#define CMP_COUNT_TO_RESTRUCT 4 // Количество сравнений, после которого реструктурируется хеш-таблица

typedef struct hash_list node_t;

struct hash_list
{
    char *key;
    node_t *node;
};

// Базовые функции списка
node_t *make_node(char *key)
{
    node_t *node = malloc(sizeof(node_t));
    if (node != NULL)
    {
        char *tmp_key = malloc(sizeof(char)*(strlen(key) + 1));
        if (tmp_key != NULL)
            strcpy(tmp_key, key);
        node->key = tmp_key;
        node->node = NULL;
    }
    return node;
}

char *pop_front(node_t **head)
{
    char *res = NULL;
    if (head == NULL || *head == NULL);
    else
    {
        res = (*head)->key;
        node_t *tmp = *head;
        *head = (*head)->node;
        free(tmp);
    }
    return res;
}

char *pop_node(node_t **head, node_t *elem)
{
    void *res = NULL;
    if (head == NULL || *head == NULL);
    else if (*head == elem)
    {
        res = elem->key;
        *head = elem->node;
        free(elem);
    }
    else
    {
        node_t *curr = *head;
        for (; curr != NULL && curr->node != elem; curr = curr->node);
        if (curr->node == elem)
        {
            res = elem->key;
            curr->node = elem->node;
            free(elem);
            elem = NULL;
        }
    }
    return res;
}

void push_front(node_t **head, node_t *elem)
{
    elem->node = *head;
    *head = elem;
}

// Структура хеш-таблицы открытого хеширования
struct hash_table_open
{
    node_t **arr;
    size_t n;
};

hto_t hto_create(void)
{
    hto_t hash_table = malloc(sizeof(struct hash_table_open));
    if (hash_table != NULL)
    {
        hash_table->arr = NULL;
        hash_table->n = 0;
    }
    return hash_table;
}

ht_rc_t hto_clear(hto_t table)
{
    ht_rc_t rc = HT_OK;
    if (table == NULL)
        rc = HT_INVALID_PARAM;
    else
    {
        for (node_t **pa = table->arr; pa < table->arr + table->n; pa++)
            while(*pa != NULL)
                free(pop_front(pa));
        free(table->arr);
        table->arr = NULL;
        table->n = 0;
    }
    return rc;
}

void hto_destroy(hto_t *table)
{
    if (table == NULL);
    else 
    {
        hto_clear(*table);
        free(*table);
        *table = NULL;
    }
}

ht_rc_t hto_insert(hto_t *table, const char *key, size_t c2restr)
{
    if (table == NULL)
        return HT_INVALID_PARAM;
    if (*table == NULL)
        *table = hto_create();
    if ((*table)->n == 0)
    {
        node_t **tmp = calloc(START_N, sizeof(node_t *));
        if (tmp == NULL)
            return HT_MEM;
        else
            (*table)->arr = tmp, (*table)->n = START_N;
    }
    ht_rc_t rc = HT_OK;
    int h = hash((char *) key, K, (*table)->n);

    size_t counter = 0;
    for (node_t *node = (*table)->arr[h]; node != NULL; node = node->node, counter++);
    if (counter < c2restr)
        push_front(&(*table)->arr[h], make_node((char *) key));
    else if ((rc = hto_restruct(table, c2restr)) == HT_OK)
        rc = hto_insert(table, key, c2restr);
    return rc;
}

ht_rc_t hto_find(hto_t table, const char *key, int *cmp_count)
{
    int h = hash((char *) key, K, table->n);
    node_t *node = table->arr[h];
    (*cmp_count)++;
    for(; node != NULL && strcmp(node->key, key) != 0; (*cmp_count)++, node = node->node);
    if (node == NULL || strcmp(node->key, key) != 0)
        return HT_NOT_FOUND;
    return HT_OK;
}

ht_rc_t hto_remove(hto_t table, char *key)
{
    if (table == NULL)
        return HT_INVALID_PARAM;
    if (table->arr == NULL)
        return HT_INVALID_PARAM;
    int h = hash((char *) key, K, table->n);
    node_t *node = table->arr[h];
    for(; node != NULL && strcmp(node->key, key) != 0; node = node->node);
    char *p = pop_node((table->arr + h), node);
    if (p == NULL)
        return HT_NOT_FOUND;
    else
    {
        free(p);
        return HT_OK;
    }
}

void print_list(node_t *list)
{
    for (node_t *node = list; node != NULL; node = node->node)
        printf("->'%s'", node->key);
    printf("\n");
}

void hto_print(hto_t table)
{
    if (table->n == 0)
        printf("Таблица пуста\n");
    for (size_t i = 0; i < table->n; i++)
        if (table->arr[i] != NULL)
            printf("%zu:", i), print_list(table->arr[i]);
}

ht_rc_t hto_restruct(hto_t *table, size_t c2restr)
{
    int new_n = get_prime((*table)->n);
    hto_t hto_tmp = hto_create();
    node_t **tmp = calloc(new_n, sizeof(node_t *));
    if (tmp == NULL)
    {
        hto_destroy(&hto_tmp);
        return HT_MEM;
    }
    ht_rc_t rc = HT_OK;
    hto_tmp->arr = tmp, hto_tmp->n = new_n;
    // printf("\nrestruct:\n");
    // hto_print(*table);
    for (size_t i = 0; i < (*table)->n; i++)
        for (node_t *node = (*table)->arr[i]; node != NULL && rc == HT_OK; node = node->node)
            rc = hto_insert(&hto_tmp, node->key, c2restr);
    if (rc == HT_OK)
        hto_destroy(table), *table = hto_tmp;
    return rc;
}

size_t get_hto_table_size(hto_t table)
{
    return table->n;
}

size_t hto_count(hto_t table)
{
    size_t res = 0;
    for (size_t i = 0; i < table->n; i++)
        for (node_t *node = table->arr[i]; node != NULL; res++, node = node->node);
    return res;
}