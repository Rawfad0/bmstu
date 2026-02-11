/**
* Модуль содержащий структуры
*/

#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include <stdint.h>

// Постоянные структур
#define MANTISS_SIZE 40
#define INT_SIZE 30
#define RES_SIZE 31
#define CALC_MANTISS_SIZE MANTISS_SIZE + INT_SIZE

// Структуры
typedef struct
{
    int8_t mantiss_sign;
    int8_t mantiss_digits[MANTISS_SIZE];
    int exp;
} real_num;

typedef struct
{
    int8_t sign;
    int8_t digits[INT_SIZE];
} int_num;

typedef struct
{
    int8_t mantiss_sign;
    int8_t mantiss_digits[CALC_MANTISS_SIZE];
    int exp;
} calc_num;

#endif

