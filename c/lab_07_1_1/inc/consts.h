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
#define RETURN_CODE_INCORRECT_ARGUMENT_COUNT 53
#define RETURN_CODE_INCORRECT_ARGUMENT 53
#define RETURN_CODE_INCORRECT_FILE 2
#define RETURN_CODE_INCORRECT_INPUT 3
#define RETURN_CODE_EMPTY_FILE 4
#define RETURN_CODE_INCORRECT_ARRAY 5
#define RETURN_CODE_INCORRECT_DST_ARRAY 6
#define RETURN_CODE_ALLOCATION_FAILED 7
#define RETURN_CODE_WRITE_ERROR 8

#endif // __CONSTS__H__
