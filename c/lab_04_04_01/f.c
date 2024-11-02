#include "f.h"
#include <string.h>

/**
 * @brief Проверка размера строки
 * 
 * @param line строка
 * @return код выхода
 *
 * Если строка больше чем LINE_MAX+1, то функция возвращает код ошибки
 * соответствующий EXIT_CODE_INCORRECT_LINE_SIZE, иначе 0.
 */
int is_valid_line(char *line)
{
    if (strlen(line) > LINE_MAX+1)
        return EXIT_CODE_INCORRECT_LINE_SIZE;
    return 0;
}

/**
 * @brief Количество знаков подряд
 * 
 * @param line строка
 * @return количество знаков (0 или 1) или код ошибки
 *
 * С помощью функции strspn функция считает количество подряд идущих
 * символов SIGNS и если оно равно 0 или 1, то возвращает их количество
 * в противном случае возвращает EXIT_CODE_RE_MISMATCH.   
 */
int sign_part(char *line)
{
    size_t r;
    r = strspn(line, SIGNS);
    if (r > 1)
        return EXIT_CODE_RE_MISMATCH;
    return (int) r;
}

/**
 * @brief Длина дробной части
 * 
 * @param line строка
 * @return длина или код ошибки
 *
 * С помощью функции strspn функция считает количество подряд идущих
 * символов POINT и если оно равно 0, то возвращает 0, 
 * если 1, то с помощью функции strspn функция считает количество 
 * подряд идущих символов DIGITS и возвращает их количество + 1 (точка)
 * если количество точек больше 1, то возвращает EXIT_CODE_RE_MISMATCH.   
 */
int point_part(char *line)
{
    size_t i = 0;
    size_t r;
    // Точка
    r = strspn(line, POINT);
    if (r == 0)
        return 0;
    if (r > 1)
        return EXIT_CODE_RE_MISMATCH;  // Больше одной точки
    i += r;
    // Цифры
    r = strspn(line + i, DIGITS);
    i += r;
    return (int) i;
}

/**
 * @brief Длина экспоненциальной части
 * 
 * @param line строка
 * @return длина или код ошибки
 *
 * Функция посимвольно итерируется по строке и проверяет её соответствие 
 * регулярному выражению: ([eE][+-]?\d+)? 
 * в случае соответствия возвращает длину соответствующего участка,
 * в протвном случае возвращет код EXIT_CODE_RE_MISMATCH.
 */
int e_part(char *line)
{
    int i = 0;
    int r;
    // Е
    r = strspn(line + i, EE);
    if (r == 0)
        return i;   // 0
    if (r > 1)
        return EXIT_CODE_RE_MISMATCH;
    i += r;
    // Знак
    r = sign_part(line + 1);
    if (r == EXIT_CODE_RE_MISMATCH)
        return EXIT_CODE_RE_MISMATCH;
    i += r;
    // Цифры
    r = strspn(line + i, DIGITS);
    if (r == 0)
        return EXIT_CODE_RE_MISMATCH;
    i += r;

    return i;
}

/**
 * @brief Является ли строка вещественным числом в экспоненциальной форме
 * 
 * @param line строка
 * @return YES или NO
 *
 * Функция посимвольно итерируется по строке и проверяет её соответствие 
 * регулярному выражению: [+-]?(\d+([.]\d*)?|[.]\d+)([eE][+-]?\d+)?
 */
char *is_number(char *line)
{
    size_t i = 0;   // Индекс текущего символа
    int r;          // Промежуточный индекс
    int flag_no_digits = 0;
    // Начальные пробельные символы
    i += strspn(line + i, SPACE_SYMBOLS);
    if (line[i] == '\0')
        return NO;
    // Знак
    r = sign_part(line + i);
    if (r == EXIT_CODE_RE_MISMATCH)
        return NO;
    i += r;
    // Цифры
    r = strspn(line + i, DIGITS);
    if (r == 0)
        flag_no_digits = 1;
    i += r;
    // Дробная часть
    r = (size_t) point_part(line + i);
    if (r == EXIT_CODE_RE_MISMATCH)
        return NO;
    if (r < 2 && flag_no_digits == 1)
        return NO;
    i += r;
    // Экспоненциальная часть
    r = e_part(line + i);
    if (r == EXIT_CODE_RE_MISMATCH)
        return NO;
    i += r;
    // Конечные (послечисловые) пробельные символы
    i += strspn(line + i, SPACE_SYMBOLS);
    if (line[i] == '\0')
        return YES;
    // После конечных пробельных символов строка не закончилась
    return NO;
}