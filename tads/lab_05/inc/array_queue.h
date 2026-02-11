#ifndef __ARRAY__QUEUE__H__
#define __ARRAY__QUEUE__H__

#include <stdlib.h>
#include <stdio.h>

#include "consts.h"
#include "application.h"

// Структура очереди на статическом массиве
typedef struct array_queue_struct sa_queue_t;

// Функции для работы c типом очередь
sa_queue_t *saq_init(void);

int saq_push(sa_queue_t *queue, applic_t a);

int saq_pop(sa_queue_t *queue, applic_t *a);

#endif