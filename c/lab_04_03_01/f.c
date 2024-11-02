#include "f.h"
#include "string.h"

/**
 * @brief Является ли строка уникальной
 * 
 * @param str_array массив строк
 * @param n длина массива
 * @param str строка
 * @return 0/1
 *
 * Проверяет есть ли строка str в str_array, если есть возвращает 0, 
 * если нет, т.е. строка является уникальной то возвращает 1. 
 */
int is_str_uniq(char str_array[][WORD_MAX+1], size_t n, char str[])
{
    for (size_t i = 0; i < n; i++)
        if (strncmp(str_array[i], str, WORD_MAX+1) == 0)
            return 0;
    return 1;
}

/**
 * @brief Разделяет строку по словам на массив строк
 * 
 * @param line строка
 * @param str_array массив строк
 * @param n длина массива
 * @return код возврата
 *
 * Функция разбивает строку по разделяющим сивмолам в массив строк
 */
int split_line_to_array(char *line, char str_array[][WORD_MAX+1], size_t *n)
{
    *n = 0;
    char *word = strtok(line, SEPARATORS);
    while (word)
    {
        if (strlen(word) > WORD_MAX)
            return EXIT_CODE_INCORRECT_WORD_SIZE;
        strncpy(str_array[(*n)++], word, WORD_MAX+1);
        word = strtok(NULL, SEPARATORS);
    }
    return 0;
}

/**
 * @brief Уникальные строки обрабатываются в уникальные символы и добавляются в строку
 * 
 * @param str_array массив строк
 * @param n длина массива
 * @param line строка
 *
 * Функция проверяет итерируется по массиву слов в обратном порядке и если слово не равно последнему,
 * то его строка уникальных символов добавляется в строку, строки уникальных символов строк разделяются пробелом. 
 */
void str_array_to_line(char str_array[][WORD_MAX+1], size_t n, char line[])
{
    char uniq_symbols[WORD_MAX+1];
    for (size_t i = 1; i < n; i++)
    {
        strncpy(uniq_symbols, "", 1);
        if (strncmp(str_array[n - 1 - i], str_array[n - 1], WORD_MAX+1) == 0)
            continue;
        for (size_t j = 0; j < strlen(str_array[n - 1 - i]); j++)
        {
            if (strchr(uniq_symbols, str_array[n - 1 - i][j]) != NULL)
                continue;
            strncat(uniq_symbols, &str_array[n - 1 - i][j], 1);
        }
        strncat(line, uniq_symbols, WORD_MAX+1);
        strncat(line, " ", 2);
    }
    line[strlen(line) - 1] = '\0';
}