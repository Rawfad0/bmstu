#include "io.h"

/**
 * @brief Очищение буфера ввода
 * 
 */
void clear_buff(void)
{
    while (getchar() != '\n')
        ;
}

void menu_get_selected_option(int *option)
{
    char opt_str[OPTION_LEN+1] = "\0\0\0", *end;
    printf("--------------------------------------------------\n");
    printf("---------------------  МЕНЮ  ---------------------\n");
    printf("--------------------------------------------------\n");
    printf("1. Вывод информации o программе.\n");
    printf("2. Умножение вещественного числа на целое.\n");
    printf("3. Выход из программы.\n");
    printf("Выберите действие и введите номер пункта: ");

    if (fgets(opt_str, OPTION_LEN+1, stdin) == NULL)
    {
        printf("Конец ввода. EOF\n\n");
        exit(INPUT_OPTION_ERROR);
    }
    else if (opt_str[0] == '\n')
        ;
    else if (opt_str[1] != '\n')
        clear_buff();
    else
        *option = strtol(opt_str, &end, 10);
}

void info(void)
{
    printf("\n\t* Программа предназначена для умножения действительного числа в форме [+-]m.n Е [+-]K, \n \
\t* где суммарная длина мантиссы (m+n) - до 40 значащих цифр, \n \
\t* а величина порядка K - до 5 цифр, на целое число длиной до 30 десятичных цифр. \n \
\t* Результат выдается в форме [+-]0.m1 Е [+-]K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.\n \
\t* Программа осуществляет ввод чисел с проверкой их корректности и выдает \n \
\t* либо верный результат в указанном формате (при корректных данных), \n \
\t* либо сообщение о невозможности произвести счет.\n");
    printf("Автор программы: Равашдех Фадей ИУ7-35Б.\n\n");
}

int input_real_num(char *real_num_s)
{
    // printf("Так как 0 (нуль) непредставим в нормализованном виде,\nтo убедитесь, что вводимое число не равно нулю\n");
    printf("Шкала цифр мантиссы-----------|1-------|10-------|20-------|30-------|40-\n");
    printf("-----------------------------\\|/------\\|/-------\\|/-------\\|/-------\\|/--\n");
    printf("Введите действительное число: ");
    if (fgets(real_num_s, REAL_NUM_LEN + 1, stdin) == NULL)
    {
        printf("Конец ввода. EOF\n\n");
        exit(INPUT_REAL_NUM_ERROR);
    }

    size_t real_num_len = strlen(real_num_s);

    if (real_num_s[real_num_len - 1] != '\n')
    {
        clear_buff();
        printf("Слишком длинное действительное число.\n");
        return REAL_SIZE_ERROR;
    }

    if (real_num_s[0] == '\n')
    {
        printf("Пустая строка.\n");
        return EMPTY_INPUT_ERROR;
    }
    real_num_s[strcspn(real_num_s, "\n")] = 0;  // удаление \n

    // Проверка на корректность через маску
    regex_t regex;
    regcomp(&regex, REAL_MASK, REG_EXTENDED);  // Действительного числа
    if (regexec(&regex, real_num_s, 0, NULL, 0) == REG_NOMATCH)
    {
        printf("Введенные данные не соответствуют формату входных данных.\n");
        return REAL_MASK_ERROR;
    }

    return OK;
}

int input_int_num(char *integer_num_s)
{
    printf("Шкала цифр числа-----|1-------|10-------|20-------|30-\n");
    printf("--------------------\\|/------\\|/-------\\|/-------\\|/--\n");
    printf("Введите целое число: ");
    if (fgets(integer_num_s, INT_NUM_LEN + 1, stdin) == NULL)
    {
        printf("Конец ввода. EOF\n\n");
        exit(INPUT_INTEGER_NUM_ERROR);
    }
    size_t integer_num_len = strlen(integer_num_s);

    if (integer_num_s[integer_num_len - 1] != '\n')
    {
        clear_buff();
        printf("Слишком длинное целое число.\n");
        return INT_SIZE_ERROR;
    }

    if (integer_num_s[0] == '\n')
    {
        printf("Пустая строка.\n");
        return EMPTY_INPUT_ERROR;
    }
    integer_num_s[strcspn(integer_num_s, "\n")] = 0;  // удаление \n

    // Проверка на корректность через маску
    regex_t regex;
    regcomp(&regex, INTEGER_MASK, REG_EXTENDED);  // Целого числа
    if (regexec(&regex, integer_num_s, 0, NULL, 0) == REG_NOMATCH)
    {
        printf("Введенные данные не соответствуют формату входных данных.\n");
        return INTEGER_MASK_ERROR;
    }

    return OK;
}

void print_result(char *result_num)
{
    printf("Результат: %s\n\n", result_num);
}
