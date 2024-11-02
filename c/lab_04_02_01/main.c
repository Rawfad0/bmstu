/*!
 * \file
 * \brief Задача 2
 *
 * 1. Ввести одну строку. Составить массив из слов исходной строки, 
 * каждое слово должно входить в массив только один раз. 
 * Упорядочить этот массив в лексикографическом порядке. 
 * Слова из упорядоченного массива вывести на экран, разделив одним пробелом.
 */

#include "io.h"
#include "f.h"
#include "consts.h"

int main(void)
{
    char line[LINE_MAX+1];
    int r;
    char word_set[(LINE_MAX+1) / 2][WORD_MAX+1];
    size_t n = 0;

    if (r = line_input(line), r != 0)
        return r;
    if (r = is_valid_line(line), r != 0)
        return r;

    if (r = split_line_to_array(line, word_set, &n), r != 0)
        return r;

    if (n == 0)
        return EXIT_CODE_EMPTY_ARRAY;

    str_array_sort(word_set, n);

    print_str_array(word_set, n);

    return 0;
}