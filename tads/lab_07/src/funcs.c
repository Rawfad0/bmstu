#include "funcs.h"

void print(hto_t hto_table, htc_t htc_table)
{
    if (hto_table == NULL || htc_table == NULL)
        printf("Хеш-таблица отсутствует.\n");
    else
    {
        printf("Хеш-таблица с закрытым хешированием:\n");
        htc_print(htc_table);
        printf("Хеш-таблица с открытым хешированием:\n");
        hto_print(hto_table);
    }
}

int read(bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char **filename, size_t c2restr)
{
    free(*filename), *filename = NULL;

    int rc = RC_OK;
    char *filepath = NULL;
    printf("Введите путь к файлу с данными (например: 'data/1000.txt'):\n");
    if ((rc = get_input(&filepath, stdin)) != RC_OK)
        return rc;

    rc = read_file(tree, hto_table, htc_table, filepath, c2restr);

    if (rc == RC_OK)
        *filename = filepath, printf("Файл успешно прочитан в словарь.\n");
    return rc;
}

// int read(bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char **filename, size_t c2restr)
// {
//     bin_tree_clear(tree);
//     hto_destroy(hto_table);
//     htc_destroy(htc_table);
//     free(*filename), *filename = NULL;

//     int rc = RC_OK;
//     char *filepath = NULL;
//     printf("Введите путь к файлу с данными (например: 'data/1000.txt'):\n");
//     if ((rc = get_input(&filepath, stdin)) != RC_OK)
//         return rc;

//     FILE *f = fopen(filepath, "r");
//     if (f == NULL)
//         rc = RC_INCORRECT_FILE;
//     else
//     {
//         char *tmp = NULL;
//         bt_rc_t rc_bt = BIN_TREE_OK;
//         ht_rc_t rc_hto = HT_OK;
//         ht_rc_t rc_htc = HT_OK;
//         while (!feof(f) && rc == RC_OK)
//         {
//             if (get_input(&tmp, f) != RC_OK)
//                 break;
//             // printf("Прочитанное слово: '%s'\n", tmp);
//             rc_bt = bin_tree_insert(tree, tmp);
//             rc_hto = hto_insert(hto_table, tmp, c2restr);
//             rc_htc = htc_insert(htc_table, tmp, c2restr);
//             free(tmp);
//             if (rc_bt == BIN_TREE_MEM || rc_hto == HT_MEM || rc_htc == HT_MEM)
//                 rc = RC_ALLOCATION_FAILED;
//         }
//         fclose(f);
//     }
//     if (rc == RC_OK)
//         *filename = filepath, printf("Файл успешно прочитан в словарь.\n");
//     return rc;
// }

int find(char *filename, bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, size_t c2restr)
{
    if (filename == NULL)
        return RC_INCORRECT_FILE;
    int rc = RC_OK;
    char *str = NULL;
    printf("Введите искомое слово:\n");
    if ((rc = get_input(&str, stdin)) != RC_OK)
        return rc;

    int cmp_count1 = 0;
    int cmp_count2 = 0;
    int cmp_count3 = 0;
    bt_rc_t rc_bt = bin_tree_find(*tree, str, &cmp_count1);
    ht_rc_t rc_hto = hto_find(*hto_table, str, &cmp_count2);
    ht_rc_t rc_htc = htc_find(*htc_table, str, &cmp_count3, c2restr);
    printf("Количество сравнений в дереве: %d\n", cmp_count1);
    printf("Количество сравнений в хеш-таблице с открытым хешированием: %d\n", cmp_count2);
    printf("Количество сравнений в хеш-таблице с закрытым хешированием: %d\n", cmp_count3);
    if (rc_bt == BIN_TREE_OK && rc_hto == HT_OK && rc_htc == HT_OK)
    {
        printf("Искомое слово '%s' найдено.\n", str);
        free(str);
        return rc;
    }

    char *answ = NULL;
    printf("Искомое слово не найдено. \nЖелаете добавить его?\n(Y/n):");
    if ((rc = get_input(&answ, stdin)) != RC_OK);
    else if (strcmp(answ, "Y") == 0)
        if (bin_tree_insert(tree, str) == BIN_TREE_MEM)
            rc = RC_ALLOCATION_FAILED;
        else if (hto_insert(hto_table, str, c2restr) == HT_MEM)
            rc = RC_ALLOCATION_FAILED;
        else if (htc_insert(htc_table, str, c2restr) == HT_MEM)
            rc = RC_ALLOCATION_FAILED;
        else
            printf("Слово успешно добавлено в файл.\n");
    else if (strcmp(answ, "n") != 0)
        printf("Ответ не ясен.\n");
        
    free(answ), free(str);
    return rc;
}

int remove_word(char *filename, bin_tree_t *tree, hto_t hto_table, htc_t htc_table, size_t c2restr)
{
    if (filename == NULL)
        return RC_INCORRECT_FILE;
    int rc = RC_OK;
    char *str = NULL;
    printf("Введите удаляемое слово:\n");
    if ((rc = get_input(&str, stdin)) != RC_OK)
        return rc;

    bt_rc_t rc_bt = bin_tree_remove(tree, str);
    ht_rc_t rc_hto = hto_remove(hto_table, str);
    ht_rc_t rc_htc = htc_remove(htc_table, str, c2restr);
    if (rc_bt == BIN_TREE_MEM)
        rc = RC_ALLOCATION_FAILED;
    else if (rc_bt == BIN_TREE_NOT_FOUND && rc_hto == HT_NOT_FOUND)
        printf("Cлово не найдено.\n");
    else if (rc_bt == BIN_TREE_OK)
        printf("Cлово удалено.\n");
    else if (rc_hto == HT_MEM)
        rc = RC_ALLOCATION_FAILED;
    else if (rc_hto == HT_NOT_FOUND)
        printf("Cлово не найдено.\n");
    else if (rc_hto == HT_OK)
        printf("Слово удалено.\n");
    else if (rc_htc == HT_MEM)
        rc = RC_ALLOCATION_FAILED;
    else if (rc_htc == HT_NOT_FOUND)
        printf("Cлово не найдено.\n");
    else if (rc_htc == HT_OK)
        printf("Слово удалено.\n");

    free(str);
    return rc;
}

int balance(bin_tree_t *tree)
{
    int rc = RC_OK;
    bt_rc_t rc_bt = bst_to_avl_tree(tree);
    if (rc_bt == BIN_TREE_OK)
        printf("Дерево успешно сбалансировано.\n");
    else if (rc_bt == BIN_TREE_MEM)
        printf("Дерево не удалось сбалансировать.\n"), rc = RC_ALLOCATION_FAILED;
    else
        printf("Дерево не удалось сбалансировать.\n");
    return rc;
}

int write(bin_tree_t tree)
{
    if (tree == NULL)
        return RC_INCORRECT_FILE;
    int rc = RC_OK;
    FILE *f = fopen("res.dot", "w");
    if (!f)
        rc = RC_INCORRECT_FILE;
    else
    {
        fprintf(f, "graph graphname {\n");
        bin_tree_print(tree, f);
        fprintf(f, "}\n");
    }
    if (f)
        fclose(f);
    return rc;
}

int read_file(bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char *filename, size_t c2restr)
{
    bin_tree_clear(tree);
    hto_destroy(hto_table);
    htc_destroy(htc_table);

    int rc = RC_OK;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        rc = RC_INCORRECT_FILE;
    else
    {
        char *tmp = NULL;
        bt_rc_t rc_bt = BIN_TREE_OK;
        ht_rc_t rc_hto = HT_OK;
        ht_rc_t rc_htc = HT_OK;
        while (!feof(f) && rc == RC_OK)
        {
            if (get_input(&tmp, f) != RC_OK)
                break;
            // printf("Прочитанное слово: '%s'\n", tmp);
            rc_bt = bin_tree_insert(tree, tmp);
            rc_hto = hto_insert(hto_table, tmp, c2restr);
            rc_htc = htc_insert(htc_table, tmp, c2restr);
            free(tmp);
            if (rc_bt == BIN_TREE_MEM || rc_hto == HT_MEM || rc_htc == HT_MEM)
                rc = RC_ALLOCATION_FAILED;
        }
        fclose(f);
    }
    return rc;
}

int change_c2restr(size_t *c2restr, bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char *filename)
{
    char *str = NULL, *end = NULL;
    size_t tmp = 0;
    int rc = RC_OK;
    printf("Текущее число сравнений: %zu\n", *c2restr);
    printf("Введите новое число сравнений:\n");
    if ((rc = get_input(&str, stdin)) != RC_OK)
        return rc;

    tmp = strtol(str, &end, 10);
    if (end != NULL && *end == '\0' && tmp > 0)
        *c2restr = tmp, rc = read_file(tree, hto_table, htc_table, filename, *c2restr);
    else
        rc = RC_INCORRECT_INPUT;
    free(str);
    return rc;
}
