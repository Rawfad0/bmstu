#include "hash_closed.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define START_N 11 // Начальная длина хеш-таблицы
#define COEF 2      // Увеличение в COEF раз при недопустимой коллизии
#define K 29        // k многочлена больше количества букв алфавита
#define CMP_COUNT_TO_RESTRUCT 4 // Количество сравнений, после которого реструктурируется хеш-таблица

#define CURR (char **)(pb + ((p_insert - pb) % (size_t)tl))
#define DEL ""

// Структура хеш-таблицы закрытого хеширования
struct hash_table_closed
{
    char **arr;
    size_t n;
};

htc_t htc_create(void)
{
    htc_t hash_table = malloc(sizeof(struct hash_table_closed));
    if (hash_table != NULL)
    {
        hash_table->arr = NULL;
        hash_table->n = 0;
    }
    return hash_table;
}

ht_rc_t htc_clear(htc_t table)
{
    ht_rc_t rc = HT_OK;
    if (table == NULL)
        rc = HT_INVALID_PARAM;
    else
    {
        for (char **pa = table->arr; pa < table->arr + table->n; pa++)
            free(*pa);
        free(table->arr);
        table->arr = NULL;
        table->n = 0;
    }
    return rc;
}

void htc_destroy(htc_t *table)
{
    if (table == NULL);
    else 
    {
        htc_clear(*table);
        free(*table);
        *table = NULL;
    }
}

ht_rc_t htc_insert(htc_t *table, const char *key, size_t c2restr)
{
    if (table == NULL)
        return HT_INVALID_PARAM;
    if (*table == NULL)
        *table = htc_create();
    if ((*table)->n == 0)
    {
        char **tmp = calloc(START_N, sizeof(char *));
        if (tmp == NULL)
            return HT_MEM;
        else
            (*table)->arr = tmp, (*table)->n = START_N;
    }
    ht_rc_t rc = HT_OK;
    int h = hash((char *) key, K, (*table)->n);

    size_t tl = (*table)->n;
    char **pb = (*table)->arr, **p_insert = pb + h;
    for (; p_insert - pb < h + (long int) c2restr && *CURR != NULL && strcmp(*CURR, DEL) != 0 && strcmp(*CURR, key) != 0; p_insert++);
    if (p_insert - pb >= h + (long int) c2restr && (rc = htc_restruct(table, c2restr)) == HT_OK)
        rc = htc_insert(table, key, c2restr);    // Вставка элемента после реструктуризации таблицы
    else if (*CURR == NULL || (*CURR != NULL && strcmp(*CURR, DEL) == 0))
    {
        // Ключа нет в таблице и реструктуризация хеш-таблицы не требуется
        if (*CURR != NULL && strcmp(*CURR, DEL) == 0)
            free(*CURR), *CURR = NULL;
        char *tmp_key = malloc(sizeof(char)*(strlen(key) + 1));
        if (tmp_key != NULL)
            strcpy(tmp_key, key), *CURR = tmp_key;
        else
            rc = HT_MEM;
    }
    return rc;
}

ht_rc_t htc_find(htc_t table, const char *key, int *cmp_count, size_t c2restr)
{
    int h = hash((char *) key, K, table->n);
    (*cmp_count)++;

    size_t tl = table->n;
    char **pb = table->arr, **p_insert = pb + h;
    for (; p_insert - pb < h + (long int) c2restr && *CURR != NULL && strcmp(*CURR, DEL) != 0 && strcmp(*CURR, key) != 0; p_insert++);
    *cmp_count += p_insert - (pb + h);
    if (*CURR != NULL && strcmp(*CURR, key) == 0)
        return HT_OK;
    else
        return HT_NOT_FOUND;
}

ht_rc_t htc_remove(htc_t table, char *key, size_t c2restr)
{
    if (table == NULL)
        return HT_INVALID_PARAM;
    if (table->arr == NULL)
        return HT_NOT_FOUND;
    int h = hash((char *) key, K, table->n);

    size_t tl = table->n;
    char **pb = table->arr, **p_insert = pb + h;
    for (; p_insert - pb < h + (long int) c2restr && *CURR != NULL && strcmp(*CURR, DEL) != 0 && strcmp(*CURR, key) != 0; p_insert++);

    if (*CURR != NULL && strcmp(*CURR, key) == 0)
    {
        strcpy(*CURR, "");
        return HT_OK;
    }
    else
        return HT_NOT_FOUND;
}

void htc_print(htc_t table)
{
    if (table->n == 0)
        printf("Таблица пуста\n");
    for (size_t i = 0; i < table->n; i++)
        if (table->arr[i] != NULL && strcmp(table->arr[i], DEL) != 0)
            printf("%4zu: '%s'.\n", i, table->arr[i]);
}

ht_rc_t htc_restruct(htc_t *table, size_t c2restr)
{
    int new_n = get_prime((*table)->n);
    // printf("new_n:%d\n", new_n);
    ht_rc_t rc = HT_OK;
    htc_t htc_tmp = htc_create();
    char **tmp = calloc(new_n, sizeof(char *));
    if (tmp == NULL)
    {
        htc_destroy(&htc_tmp);
        return HT_MEM;
    }
    htc_tmp->arr = tmp, htc_tmp->n = new_n;
    for (size_t i = 0; i < (*table)->n; i++)
        if ((*table)->arr[i] != NULL)
            rc = htc_insert(&htc_tmp, (*table)->arr[i], c2restr);
    if (rc == HT_OK)
        htc_destroy(table), *table = htc_tmp;
    else
        htc_destroy(&htc_tmp);
    return rc;
}

size_t get_htc_table_size(htc_t table)
{
    return table->n;
}

size_t htc_count(htc_t table)
{
    size_t res = 0;
    for (size_t i = 0; i < table->n; i++)
        if (table->arr[i] != NULL)
            res++;
    return res;
}