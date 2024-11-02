/**
 * @file consts.h
 * @brief Модуль с макросами
 * 
 */

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Количество аргумментов программы
#define ARGC_CORRECT 1

// Команды
#define COMMAND_CALCULATE "val"
#define COMMAND_DERIVATIVE "ddx"
#define COMMAND_ADD "sum"
#define COMMAND_DIVIDE "dvd"

// Коды возврата
#define RC_OK 0
#define RC_INCORRECT_ARGC 1
#define RC_INCORRECT_COMMAND 2
#define RC_ALLOCATION_FAILED 3
#define RC_INCORRECT_INPUT 4

#endif