#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include <stdlib.h>
#include <stdio.h>

#include "consts.h"


// Структура заявки
typedef struct application applic_t;

struct application
{
    double time;    // Время попадания заявки в очередь
};

// Функция создания заявки
applic_t make_application(double time);

#endif
