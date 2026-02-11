#include "funcs.h"

typedef struct list *list_t;
struct list
{
    char ch;
    list_t next;
};

int push(list_t *stack, char ch)
{
    list_t tmp = malloc(sizeof(struct list));
    if (tmp == NULL)
        return RC_ALLOCATION_FAILED;

    tmp->ch = ch;
    tmp->next = *stack;
    *stack = tmp;
    return RC_OK;
}

int pop(list_t *stack, list_t *node)
{
    if (*stack == NULL)
        return RC_STACK_EMPTY;

    *node = *stack;
    *stack = (*stack)->next;
    return RC_OK;
}

void stack_free(list_t *stack)
{
    list_t next_p = NULL;
    for ( ; *stack != NULL; *stack = next_p)
    {
        next_p = (*stack)->next;
        free(*stack);
    }
}

void node_printer(const char *key, int *value, void *n)
{
    list_t *stack = n;
    // Корень
    if (*stack == NULL)
    {
        printf("'%s' - %d\n", key, *value); // Вывод узла
        push(stack, 'l');                  // Переход влево
        return;
    }
    // Не корень => Отрисовка путей в дереве
    list_t rev_stack = NULL;
    for (list_t node = (*stack)->next; node != NULL; node = node->next)
        push(&rev_stack, node->ch);
    for (list_t node = rev_stack; node != NULL; node = node->next)
        if (node->ch == 'l')
            printf("│   ");
        else
            printf("    ");
    stack_free(&rev_stack);
    if ((*stack)->ch == 'l')
            printf("├── ");
        else
            printf("└── ");
    // Вывод узла
    if (key == NULL && value == NULL)
        printf("NULL\n"); 
    else
        printf("'%s' - %d\n", key, *value);
    // Изменение стека
    if (key == NULL && value == NULL)
    {
        if ((*stack)->ch == 'l')
            (*stack)->ch = 'r'; // Переход из левого терминального узла в право
        else
        {
            list_t node;
            while (*stack != NULL && (*stack)->ch == 'r')
                pop(stack, &node), free(node);  // Возврат по правой стороне до упора
            if (*stack != NULL)
                (*stack)->ch = 'r';   // Переход с левой стороны на правую
        }
    }
    else
        push(stack, 'l');
}

void print_freq_list(bin_tree_t tree)
{
    list_t stack = NULL;
    printf("Вывод дерева:\n");
    if (tree == NULL)
        printf("Дерево отсутствует.\n");
    else
        bin_tree_each(tree, (*node_printer), &stack), stack_free(&stack);
}

int read_freq_list(bin_tree_t *tree, char **filename)
{
    bin_tree_clear(tree);
    free(*filename);

    int rc = RC_OK;
    char *filepath = NULL;
    printf("Введите путь к файлу с данными (например: 'data/1000.txt'):\n");
    if ((rc = get_input(&filepath, stdin)) != RC_OK)
        return rc;

    FILE *f = fopen(filepath, "r");
    if (f == NULL)
        rc = RC_INCORRECT_FILE;
    else
    {
        char *tmp = NULL;
        bt_rc_t rc_bt = BIN_TREE_OK;
        while (!feof(f) && rc == RC_OK)
        {
            if (get_input(&tmp, f) != RC_OK)
                break;
            // printf("Прочитанное слово: '%s'\n", tmp);
            rc_bt = bin_tree_insert(tree, tmp);
            free(tmp);
            if (rc_bt == BIN_TREE_MEM)
                rc = RC_ALLOCATION_FAILED;
        }
        fclose(f);
    }
    if (rc == RC_OK)
        *filename = filepath, printf("Файл успешно прочитан в словарь.\n");
    return rc;
}

int find_in_file(char *filename, char *str, int *res, int *cmp_count)
{
    int rc = RC_OK;
    if (filename == NULL)
        return RC_INCORRECT_FILE;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return RC_INCORRECT_FILE;
    char *tmp = NULL;
    while (!feof(f) && rc == RC_OK)
    {
        if (get_input(&tmp, f) != RC_OK)
            break;
        (*cmp_count)++;
        // printf("%d:%s\n", *cmp_count, tmp);
        if (strcmp(str, tmp) == 0)
        {
            (*res)++;
            free(tmp);
            break;
        }
        free(tmp);
    }
    fclose(f);
    return rc;
}

int find_in_freq_list(bin_tree_t *tree, char *filename)
{
    int rc = RC_OK;
    char *str = NULL;
    printf("Введите искомое слово:\n");
    if ((rc = get_input(&str, stdin)) != RC_OK)
        return rc;

    int res = 0;
    int *num = NULL;
    int cmp_count1 = 0, cmp_count2 = 0;
    bt_rc_t rc_bt = bin_tree_find(*tree, str, &num, &cmp_count1);
    if ((rc = find_in_file(filename, str, &res, &cmp_count2)) != RC_OK)
    {
        free(str);
        return rc;
    }

    printf("Количество сравнений в дереве: %d\n", cmp_count1);
    printf("Количество сравнений в файле: %d\n", cmp_count2);
    if (rc_bt == BIN_TREE_OK && res > 0)
    {
        printf("Искомое слово '%s' найдено в дереве и в файле.\n", str);
        free(str);
        return rc;
    }
    else if (rc_bt == BIN_TREE_OK && res == 0)
    {
        printf("Искомое слово '%s' найдено в дереве, но не в файле.\n", str);
        printf("Рекомендуется считать частотный словарь из файла еще раз.\n");
        free(str);
        return rc;
    }
    else if (rc_bt == BIN_TREE_NOT_FOUND && res != 0)
    {
        printf("Искомое слово '%s' найдено в файле, но не в дереве.\n", str);
        printf("Рекомендуется считать частотный словарь из файла еще раз.\n");
        free(str);
        return rc;
    }

    char *answ = NULL;
    printf("Искомое слово не найдено в дереве и в файле. \nЖелаете добавить его?\n(Y/n):");
    if ((rc = get_input(&answ, stdin)) != RC_OK)
        return rc;
    if (strcmp(answ, "Y") == 0)
    {
        FILE *f = fopen(filename, "a");
        if (f == NULL)
            rc = RC_INCORRECT_FILE;
        else
        {
            fprintf(f, "\n%s", str);
            fclose(f);
            printf("Слово успешно добавлено в файл.\n");
        }
        if (rc == RC_OK)
        {
            bt_rc_t rc_bt = bin_tree_insert(tree, str);
            if (rc_bt == BIN_TREE_MEM)
                    rc = RC_ALLOCATION_FAILED;
        }
    }
    else if (strcmp(answ, "n") != 0)
        printf("Ответ не ясен.\n");
        
    free(answ), free(str);
    return rc;
}
