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
#define VALUE_LEN 

//
#define OPTION_LEN 2
#define REPEAT 10

// Действие
#define OPT_PRINT_INFO 0
#define OPT_READ 1
#define OPT_D_ALG 2
#define OPT_FW_ALG 3
#define OPT_WRITE 4
#define OPT_EXIT 5

// RETURN CODES - Коды возврата
#define RC_OK 0
#define RC_ALLOCATION_FAILED 1
#define RC_INPUT_ERROR_EOF 2
#define RC_INCORRECT_INPUT 3
#define RC_INCORRECT_OPTION 4
#define RC_EMPTY_STR 5
#define RC_INCORRECT_FILE 6
#define RC_STACK_EMPTY 11
#define RC_INCORRECT_DATA 21

#endif
