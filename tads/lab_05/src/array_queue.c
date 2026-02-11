#include "array_queue.h"

#define MAX_ARR_LEN 100

struct array_queue_struct
{
    applic_t array[MAX_ARR_LEN];    // Статисческий массив заявок
    size_t len;                     // Кол-во элементов

    applic_t* q_1;              // Адрес нижней границы
    applic_t* q_m;              // Адрес верхней границы
    applic_t* p_in;             // Указатель за последний элемент
    applic_t* p_out;            // Указатель на первый элемент
};

sa_queue_t *saq_init(void)
{
    sa_queue_t *queue = malloc(sizeof(sa_queue_t));

    queue->len = 0;
    queue->q_1 = queue->array;
    queue->q_m = queue->array + MAX_ARR_LEN;
    queue->p_in = queue->q_1;
    queue->p_out = queue->p_in;

    return queue;
} 

int saq_push(sa_queue_t *queue, applic_t a)
{
    if (queue->len == MAX_ARR_LEN)
        return RC_QUEUE_FULL;

    *(queue->p_in) = a;
    queue->p_in++;
    queue->len++;

    if (queue->p_in == queue->q_m + 1)
        queue->p_in = queue->q_1;
    return RC_OK;
}

int saq_pop(sa_queue_t *queue, applic_t *a)
{
    if (queue->len == 0)
        return RC_QUEUE_EMPTY;

    *a = *(queue->p_out);
    queue->p_out++;
    queue->len--;

    if (queue->p_out == queue->q_m + 1)
        queue->p_out = queue->q_1;
    return RC_OK;
}

void saq_print_info(sa_queue_t *queue);
