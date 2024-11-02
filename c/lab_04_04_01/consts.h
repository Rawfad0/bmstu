/**
* Модуль содержащий константы
*/

#ifndef __CONSTS__H__
#define __CONSTS__H__

// Директивы препроцессора
#include <stddef.h>

// Размеры массивов
#define LINE_MAX 256
#define WORD_MAX 16

// Наборы символов
#define SPACE_SYMBOLS " \n\r\t\v\f"
#define SIGNS "+-"
#define DIGITS "0123456789"
#define EE "eE"
#define POINT "."

// Результат YES/NO
#define YES "YES"
#define NO "NO"

// Коды возврата
#define EXIT_CODE_INCORRECT_LINE_SIZE 1
#define EXIT_CODE_RE_MISMATCH -1

#endif // __CONSTS__H__
