/**
 * @file consts.h
 * @brief Модуль с макросами
 * 
 */

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Количество аргумментов программы
#define CORRECT_ARGC 3

// Аргументы
#define FILE_IN argv[1] 
#define FILE_OUT argv[2]

// Коды возврата
#define RC_OK 0
#define RC_INCORRECT_ARGC 1
#define RC_ALLOCATION_FAILED 3
#define RC_INCORRECT_FILE 4
#define RC_EMPTY_FILE 5
#define RC_INCORRECT_INPUT 6
#define RC_WRITE_ERROR 7

#endif