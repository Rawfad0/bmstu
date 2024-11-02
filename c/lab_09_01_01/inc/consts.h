/**
 * @file consts.h
 * @brief Модуль с макросами
 * 
 */

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Количество аргумментов программы
#define ARGC_WITH_KEY 4
#define ARGC_WITHOUT_KEY 3 

// Аргументы
#define FILENAME argv[1]
#define FIELD argv[2]
#define KEY argv[3]

// Коды возврата
#define RC_OK 0
#define RC_INCORRECT_ARG_COUNT 1
#define RC_INCORRECT_FIELD 2
#define RC_INCORRECT_FILE 3
#define RC_INCORRECT_INPUT 4
#define RC_ALLOCATION_FAILED 5
#define RC_EMPTY_FILE 6
#define RC_INCORRECT_KEY 7

#endif
