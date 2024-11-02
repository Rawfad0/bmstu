#include "io.h"
#include <stdio.h>

/**
 * @brief Запрос строки
 * 
 * @param line строка для записи
 * @return код выхода
 *
 * Функция запрашивает строку длиной LINE_MAX+1 из входного потока
 */
int line_input(char *line)
{
    if (fgets(line, LINE_MAX+1, stdin))
        return 0;
    return EXIT_CODE_EMPTY_INPUT;
}

/**
 * @brief Вывод результата
 * 
 * @param new_str результат
 * 
 * Функция выводит строку Result: new_str, содержащую результат выполнения программы.
 */
void print_result(char new_str[])
{
    printf("Result: %s\n", new_str);
}