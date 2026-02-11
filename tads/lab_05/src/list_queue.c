#include "list_queue.h"

typedef struct list list_t; 
struct list
{
    list_t *next;   // Указатель на следующий элемент списка
    applic_t a;     // Заявка
};

struct list_queue_struct
{
    list_t **p_in;
    list_t *p_out;
};

list_t *make_node(applic_t a)
{
    list_t *tmp = malloc(sizeof(list_t));
    tmp->next = NULL;
    tmp->a = a;
    return tmp;
}

// Функции для работы c типом очередь
ll_queue_t *llq_init(void)
{
    ll_queue_t *queue = malloc(sizeof(ll_queue_t));

    queue->p_in = NULL;
    queue->p_out = NULL;

    return queue;
}

int llq_push(ll_queue_t *queue, applic_t a)
{
    list_t *tmp = make_node(a);
    if (queue->p_out == NULL)
    {
        queue->p_out = tmp;
        queue->p_in = &(tmp->next);
    }
    else
        *(queue->p_in) = tmp;
    queue->p_in = &(tmp->next);

    return RC_OK;
}

int llq_pop(ll_queue_t *queue, applic_t *a)
{
    if (queue->p_out == NULL)
        return RC_QUEUE_EMPTY;
    *a = queue->p_out->a;
    list_t *tmp = queue->p_out;
    queue->p_out = queue->p_out->next;
    free(tmp);

    return RC_OK;
}

void llq_free(ll_queue_t *queue)
{
    applic_t a;
    while (queue->p_out != NULL)
        llq_pop(queue, &a);
}
