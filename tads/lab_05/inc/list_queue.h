#ifndef __LIST__QUEUE__H__
#define __LIST__QUEUE__H__

#include <stdlib.h>
#include <stdio.h>

#include "consts.h"
#include "application.h"

// Структура очереди на односвязном списке
typedef struct list_queue_struct ll_queue_t;

// Функции для работы c типом очередь
ll_queue_t *llq_init(void);

int llq_push(ll_queue_t *queue, applic_t a);

int llq_pop(ll_queue_t *queue, applic_t *a);

void llq_free(ll_queue_t *queue);

#endif
