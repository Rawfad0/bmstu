/**
* Модуль содержащий константы
*/

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Числа
#define ARGC_1_FILE_INPUT 4
#define ARGC_2_FILE_INPUT 5

// Машинное эпсилон
#define MACHINE_EPS 0.000000001

// Ключи-действия
#define ACTION_ADDITION "a"
#define ACTION_MULTIPLICATION "m"
#define ACTION_OPERATION "o"

// Коды возврата
#define RC_OK 0
#define RC_INCORRECT_ARG_COUNT 1
#define RC_INCORRECT_ACTION 2
#define RC_INCORRECT_FILE 3
#define RC_INCORRECT_INPUT 4
#define RC_INCORRECT_COUNTER 5
#define RC_INCORRECT_SIZE 6
#define RC_ALLOCATION_FAILED 7
#define RC_UNSOLVABLE_MATRIX 8

#endif // __CONSTS__H__
