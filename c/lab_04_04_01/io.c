#include "io.h"
#include <stdio.h>

/**
 * @brief Запрос строки
 * 
 * @param line строка для записи
 * @return код выхода
 *
 * Функция запрашивает строку длиной LINE_MAX+3 из входного потока
 */
int line_input(char *line)
{
    fgets(line, LINE_MAX+3, stdin);
    return 0;
}

/**
 * @brief Вывод результата
 * 
 * @param new_str результат
 * 
 * Функция выводит строку new_str, содержащую результат выполнения программы.
 */
void print_result(char new_str[])
{
    printf("%s\n", new_str);
}