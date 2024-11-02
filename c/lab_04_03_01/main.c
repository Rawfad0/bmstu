/*!
 * \file
 * \brief Задача 3
 *
 * 1. Оставить в слове только первые вхождения каждой буквы.
 */

#include "io.h"
#include "f.h"
#include "consts.h"
#include <string.h>

int main(void)
{
    char line[LINE_MAX+1];
    int r;
    char word_arr[(LINE_MAX+1) / 2][WORD_MAX+1];
    size_t n = 0;
    char new_line[LINE_MAX+1] = "";

    if (r = line_input(line), r != 0)
        return r;

    if (r = split_line_to_array(line, word_arr, &n), r != 0)
        return r;


    str_array_to_line(word_arr, n, new_line);

    if (strcmp(new_line, "") == 0)
        return EXIT_CODE_EMPTY_STR;

    print_result(new_line);

    return 0;
}
