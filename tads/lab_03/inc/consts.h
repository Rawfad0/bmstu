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

// Количество входных параметров
#define ARGC_0_INPUT 1
#define ARGC_1_INPUT 2
#define ARGC_2_INPUT 3

//
#define OPTION_LEN 2
#define REPEAT 1000

// Сокращения значений элементов
#define VALUE1 matrix1.a[j1_i]
#define VALUE2 matrix2.a[j2_i]

// Маски регулярных выражений
#define SIZE_MASK "^[1-9][0-9]{0,3}$"
#define VAL_NUM_MASK "^[0-9]{0,7}$"
#define VALUE_MASK "^[+-]?[1-9][0-9]{0,5}$"

// Действие
#define OPT_PRINT_INFO 0
#define OPT_INPUT_MATRIX_1 1
#define OPT_INPUT_MATRIX_2 2
#define OPT_PRINT_MATRIX_1 3
#define OPT_PRINT_MATRIX_2 4
#define OPT_PRINT_SUM_STD 5
#define OPT_PRINT_SUM_SPR 6
#define OPT_COMPARISON 7
#define OPT_EXIT 8

// RETURN CODES - Коды возврата
#define RC_OK 0
#define RC_INCORRECT_ARG_COUNT 1
#define RC_INCORRECT_FILE 2
#define RC_INCORRECT_FILE_INPUT 3
#define RC_INCORRECT_COUNTER 4
#define RC_INCORRECT_SIZE 5
#define RC_ALLOCATION_FAILED 6
#define RC_INCORRECT_OPTION 7
#define RC_INPUT_ERROR 8
#define RC_INCORRECT_INPUT 9
#define RC_INVALID_MATRIX 10

//
#define VALID_MATRIX 1
#define INVALID_MATRIX 0

#endif
