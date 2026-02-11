/**
* Модуль содержащий константы
*/

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Длины строковых данных
#define REAL_NUM_LEN 49
#define INT_NUM_LEN 32
#define OPTION_LEN 2

#define EXP_MAX 99999 // Максимальный порядок по модулю

// Коды возврата
#define OK 0
#define INCORRECT_OPTION 100
#define INPUT_REAL_NUM_ERROR 1
#define INPUT_INTEGER_NUM_ERROR 2
#define REAL_MASK_ERROR 3
#define INTEGER_MASK_ERROR 4
#define EXP_SIZE_ERROR 5
#define MANTISS_SIZE_ERROR 6
#define INT_SIZE_ERROR 7
#define REAL_SIZE_ERROR 8
#define EMPTY_INPUT_ERROR 9
#define ZERO_ERROR 10
#define INPUT_OPTION_ERROR 11

// Маски регулярных выражений
#define REAL_MASK "^([+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?||[.][0-9]+([eE][+-]?[0-9]+)?)$)"
#define INTEGER_MASK "^([+-]?[0-9]+)$"

#endif // __CONSTS__H__
