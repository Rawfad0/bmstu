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

void node_printer(const char *key, void *n)
{
    list_t *stack = n;
    // Корень
    if (*stack == NULL)
    {
        printf("'%s'\n", key); // Вывод узла
        push(stack, 'l');           // Переход влево
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
    if (key == NULL)
        printf("NULL\n"); 
    else
        printf("'%s'\n", key);
    // Изменение стека
    if (key == NULL)
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

void print(bin_tree_t bin_tree, avl_tree_t avl_tree)
{
    list_t stack = NULL;
    printf("Вывод дерева:\n");
    if (bin_tree == NULL)
        printf("Дерево отсутствует.\n");
    else
    {
        printf("Двоичное дерево поиска:\n");
        bin_tree_each(bin_tree, (*node_printer), &stack), stack_free(&stack);
        printf("АВЛ-дерево:\n");
        avl_tree_each(avl_tree, (*node_printer), &stack), stack_free(&stack);
    }
}

int read(bin_tree_t *bin_tree, avl_tree_t *avl_tree, char **filename)
{
    bin_tree_clear(bin_tree);
    avl_tree_clear(avl_tree);
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
            printf("Прочитанное слово: '%s'\n", tmp);
            if ((rc_bt = bin_tree_insert(bin_tree, tmp)) == BIN_TREE_MEM)
                rc = RC_ALLOCATION_FAILED;
            else if ((rc_bt = avl_tree_insert(avl_tree, tmp)) == BIN_TREE_MEM)
                rc = RC_ALLOCATION_FAILED;

            free(tmp);
        }
        fclose(f);
    }
    if (rc == RC_OK)
        *filename = filepath, printf("Файл успешно прочитан в словарь.\n");
    return rc;
}

int find(bin_tree_t *bin_tree, avl_tree_t *avl_tree, char *filename)
{
    int rc = RC_OK;
    char *str = NULL;
    printf("Введите искомое слово:\n");
    if ((rc = get_input(&str, stdin)) != RC_OK)
        return rc;

    int cmp_count1 = 0, cmp_count2 = 0;
    bt_rc_t rc_bt1 = bin_tree_find(*bin_tree, str, &cmp_count1);
    bt_rc_t rc_bt2 = avl_tree_find(*avl_tree, str, &cmp_count2);
    

    printf("Количество сравнений в двоичном дереве поиска: %d\n", cmp_count1);
    printf("Количество сравнений в АВЛ-дереве: %d\n", cmp_count2);
    if (rc_bt1 == BIN_TREE_OK && rc_bt2 == BIN_TREE_OK)
    {
        printf("Искомое слово '%s' найдено в ДДТ и в АВЛ-дереве.\n", str);
        free(str);
        return rc;
    }
    else if (rc_bt1 == BIN_TREE_OK && rc_bt2 != BIN_TREE_OK)
    {
        printf("Искомое слово '%s' найдено в ДДТ, но не в АВЛ-дереве.\n", str);
        free(str);
        return rc;
    }
    else if (rc_bt1 != BIN_TREE_OK && rc_bt2 == BIN_TREE_OK)
    {
        printf("Искомое слово '%s' найдено в АВЛ-дереве, но не в ДДТ.\n", str);
        printf("Рекомендуется считать частотный словарь из файла еще раз.\n");
        free(str);
        return rc;
    }

    char *answ = NULL;
    printf("Искомое слово не найдено в ДДТ и в АВЛ-дереве. \nЖелаете добавить его?\n(Y/n):");
    if ((rc = get_input(&answ, stdin)) != RC_OK)
        return rc;
    if (strcmp(answ, "Y") == 0)
    {
        bt_rc_t rc_bt = bin_tree_insert(bin_tree, str);
        if (rc_bt == BIN_TREE_MEM)
                rc = RC_ALLOCATION_FAILED;
        rc_bt = avl_tree_insert(avl_tree, str);
        if (rc_bt == BIN_TREE_MEM)
                rc = RC_ALLOCATION_FAILED;
        if (rc == RC_OK)
            printf("Слово успешно добавлено.\n");
    }
    else if (strcmp(answ, "n") != 0)
        printf("Ответ не ясен.\n");
        
    free(answ), free(str);
    return rc;
}
