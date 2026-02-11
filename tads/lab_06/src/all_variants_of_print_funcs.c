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

/**
 * ВАРИАЦИЯ TREE С NULL'АМИ
 */
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

/**
 * ВАРИАЦИЯ TREE БЕЗ NULL'ОВ
 */
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
    // Не корень => Отрисовка путей в дереве и вывод узла
    if (key != NULL && value != NULL)
    {
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
        printf("'%s' - %d\n", key, *value);
    }
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

/**
 * ВАРИАЦИЯ TREE С ОТСЕЧЕНИЕМ ПОСЛЕ ПРАВОГО УЗЛА
 */
void print_freq_list(bin_tree_t tree)
{
    list_t stack = NULL;
    printf("Вывод дерева:\n");
    if (tree == NULL)
        printf("Дерево отсутствует.\n");
    else
        bin_tree_each(tree, (*node_printer), &stack), stack_free(&stack);
}

void print_node(const char *key, int *value, void *n)
{
    int counter = *((int *)n);
    for (int i = 0; i < counter - 1; i++)
        printf("│   ");
    if (counter > 0)
        printf("├── ");
    if (key == NULL && value == NULL)
        printf("NULL\n");
    else
        printf("'%s' - %d\n", key, *value);
}

/**
 * ВАРИАЦИЯ TREE БЕЗ ОТСЕЧЕНИЯ ПОСЛЕ ПРАВОГО УЗЛА
 */
void print_freq_list(bin_tree_t tree)
{
    int n = 0;
    printf("Вывод дерева:\n");
    if (tree == NULL)
        printf("Дерево отсутствует.\n");
    else
        bin_tree_print(tree, (*print_node), &n);
}

/**
 * ОБХОД ДЕРЕВА ДЛЯ ВАРИАЦИИ TREE БЕЗ ОТСЕЧЕНИЯ ПОСЛЕ ПРАВОГО УЗЛА
 */
void bin_tree_print(const bin_tree_t tree, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (tree != NULL)
    {
        (*action)(tree->data.key, &tree->data.value, param);
        (*((int *)param))++;

        if (tree->left == NULL && tree->right != NULL)
            (*action)(NULL, NULL, param);
        else
            bin_tree_print(tree->left, action, param);

        if (tree->left != NULL && tree->right == NULL)
            (*action)(NULL, NULL, param);
        else
            bin_tree_print(tree->right, action, param);

        (*((int *)param))--;
    }
}
