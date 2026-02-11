/**
* Модуль содержащий константы
*/

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Размеры и форматирование вывода
#define MAX_OPT_N 100
#define OPT_LEN 134
#define OPT_NUM_SIZE 3
#define BLANKSx25 "-------------------------"
#define BLANKSx150 "------------------------------------------------------------------------------------------------------------------------------------------------------"
#define PRINT_MAX_N 80
#define PRINT_MAX_M 20
#define SIZE_PADDING 4
#define VALUE_PADDING 6
#define SIZE_LEN 5
#define VAL_NUM_LEN 8
#define VALUE_LEN 7

//
#define OPTION_LEN 2
#define REPEAT 1000

// Действие
#define OPT_PRINT_INFO 0
#define OPT_ADD_SAS 1
#define OPT_DEL_SAS 2
#define OPT_PRNT_SAS 3
#define OPT_ADD_LLS 4
#define OPT_DEL_LLS 5
#define OPT_PRNT_LLS 6
#define OPT_PRINT_FREED_AREAS 7
#define OPT_DETERM_PALINDROM 8
#define OPT_COMPARE 9
#define OPT_EXIT 10
// #define OPT_ADD_DAS 11
// #define OPT_DEL_DAS 12
// #define OPT_PRNT_DAS 13

// RETURN CODES - Коды возврата
#define RC_OK 0
#define RC_ALLOCATION_FAILED 1
#define RC_INPUT_ERROR 2
#define RC_INCORRECT_INPUT 3
#define RC_INCORRECT_OPTION 4
#define RC_EMPTY_STR 5
#define RC_INCORRECT_FILE 6
// RC - Коды возвраты стека
#define RC_STACK_EMPTY 11
#define RC_STACK_FULL 12

#endif
