#include "list.h"

// Структура списка
struct node
{
    void *data;
    node_t *node; 
};

// Базовые функции списка
node_t *make_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));
    if (node != NULL)
    {
        node->data = data;
        node->node = NULL;
    }
    return node;
}

void *get_data(node_t *head)
{
    void *res = NULL;
    if (head != NULL)
        res = head->data;
    return res;
}

node_t *next_node(node_t *head)
{
    node_t *res = NULL;
    if (head != NULL)
        res = head->node;
    return res;
}

// Задачи на работу с одним элементом списка
void *pop_front(node_t **head)
{
    void *res = NULL;
    if (head == NULL || *head == NULL);
    else
    {
        res = (*head)->data;
        node_t *tmp = *head;
        *head = (*head)->node;
        free(tmp);
    }
    return res;
}

void *pop_node(node_t **head, node_t *elem)
{
    void *res = NULL;
    if (head == NULL || *head == NULL);
    else if (*head == elem)
    {
        res = elem->data;
        *head = elem->node;
        free(elem);
    }
    else
    {
        node_t *curr = *head;
        for (; curr != NULL && curr->node != elem; curr = curr->node);
        if (curr->node == elem)
        {
            res = elem->data;
            curr->node = elem->node;
            free(elem);
            elem = NULL;
        }
    }
    return res;
}

void *pop_back(node_t **head)
{
    void *res = NULL;
    if (head == NULL || *head == NULL);
    else if ((*head)->node == NULL)
    {
        res = (*head)->data;
        free(*head);
        *head = NULL;
    }
    else
    {
        node_t *curr = *head;
        for (; curr->node->node != NULL; curr = curr->node);
        res = curr->node->data;
        free(curr->node);
        curr->node = NULL;
    }
    return res;
}

void *pop_after(node_t *head)
{
    void *res = NULL;
    if (head == NULL);
    else
    {
        res = head->node->data;
        node_t *tmp = head->node;
        head->node = head->node->node;
        free(tmp);
    }
    return res;
}

void push_front(node_t **head, node_t *elem)
{
    elem->node = *head;
    *head = elem;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (*head == before)
    {
        elem->node = *head;
        *head = elem;
    }
    else
    {
        node_t *curr = *head;
        for (; curr != NULL && curr->node != before; curr = curr->node);
        if (curr->node == before)
        {
            elem->node = curr->node;
            curr->node = elem;
        }
    }
}

// Задача на работу с целым списком
node_t *reverse(node_t *head)
{
    node_t *new_head = NULL;
    if (head == NULL);
    else if (head->node == NULL)
        new_head = head;
    else
    {
        new_head = reverse(head->node);
        head->node->node = head;
        head->node = NULL;
    }
    return new_head;
}

// Задача на сортировку
void front_back_split(node_t *head, node_t **back);

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *res = NULL;
    if (head == NULL || head->node == NULL)
        res = head;
    else
    {
        node_t *back = NULL;
        front_back_split(head, &back);
        head = sort(head, comparator);
        back = sort(back, comparator);
        res = sorted_merge(&head, &back, comparator);
    }
    return res;
}

void front_back_split(node_t *head, node_t **back)
{
    size_t n = 0;
    for (node_t *curr = head; curr != NULL; curr = curr->node, n++);
    
    size_t mid_i = (n - 1) / 2;
    node_t *curr = head;
    for (size_t i = 0; i != mid_i; curr = curr->node, i++);

    *back = curr->node;
    curr->node = NULL;
}

node_t **merge_add_elem(node_t **curr, node_t **head)
{
    *curr = *head;
    *head = (*head)->node;
    return &((*curr)->node);
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t *tmp = NULL;
    node_t **curr = &tmp;
    node_t **head = curr;
    while (*head_a != NULL && *head_b != NULL)
        if (comparator((*head_a)->data, (*head_b)->data) < 0)
            curr = merge_add_elem(curr, head_a);
        else
            curr = merge_add_elem(curr, head_b);
    if (*head_a != NULL)
        *curr = *head_a, *head_a = NULL;
    if (*head_b != NULL)
        *curr = *head_b, *head_b = NULL;
    return *head;
}
