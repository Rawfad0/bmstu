/**
* Модуль содержащий константы
*/

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Числа
#define ARGC_NO_FILTER 3
#define ARGC_FILTER 4

// Аргументы
#define FILE_IN argv[1] 
#define FILE_OUT argv[2]
#define F_ARG argv[3]


// Ключи-аргументы программы
#define FILTER_KEY "f"

// Коды возврата
#define RC_DL_FAILED -1
#define RC_DL_FUNC_FAILED -2
#define RC_INCORRECT_ARGUMENT_COUNT 53
#define RC_INCORRECT_ARGUMENT 53
#define RC_OK 0
#define RC_INCORRECT_FILE 2
#define RC_INCORRECT_INPUT 3
#define RC_EMPTY_FILE 4
#define RC_INCORRECT_ARRAY 5
#define RC_INCORRECT_DST_ARRAY 6
#define RC_ALLOCATION_FAILED 7
#define RC_WRITE_ERROR 8

#endif // __CONSTS__H__
