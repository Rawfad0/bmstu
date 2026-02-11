#include "ui.h"

/**
 * @brief Очистка буфера ввода
 * 
 */
void clear_buff(void)
{
    while (getchar() != '\n')
        ;
}

int get_input(char **str, FILE *f)
{
    size_t len = 0;
    int read;

    if ((read = getline(str, &len, f)) == -1 || read <= 1)
    {
        // printf("read: %d\nlen: %zu\nstr: '%s'\n", read, len, *str);
        free(*str);
        return RC_INCORRECT_INPUT;
    }
    if ((*str)[strlen(*str) - 1] == '\n')
        (*str)[strlen(*str) - 1] = '\0';

    // printf("read: %d\nlen: %zu\nstr: '%s'\n", read, len, *str);

    return RC_OK;
}

int get_n_input(char pch[], size_t n)
{
    char str[n + 1];
    for (size_t i = 0; i < n + 1; i++)
        str[i] = '\0';
    if (fgets(str, n + 1, stdin) == NULL)
        return RC_INPUT_ERROR_EOF;
    else if (str[0] == '\n')
        ;
    else if (str[n - 1] != '\n' && str[n - 1] != '\0')
        clear_buff();   // Если превышен буфер в n символов, то очистка оставшегося буфера
    else
    {
        strcpy(pch, str);
        return RC_OK;
    }
    return RC_INCORRECT_INPUT;
}

void print_menu(void)
{
    char options[MAX_OPT_N][2*OPT_LEN] = {"Информация о программе",
        "Считать данные из файла",
        "Вывести данные в виде ДДТ и хеш-таблицы",
        "Найти слово",
        "Удалить слово",
        "Сбалансировать дерево",
        "Сравнение типов данных",
        "Сравнение хеш-таблиц",
        "Выйти"};
    
    // Шапка меню
    printf("+%.*s+\n", OPT_LEN, BLANKSx150);
    printf("|%*sМЕНЮ%*s|\n", OPT_LEN/2 - 2, " ", OPT_LEN/2 - 2, " ");
    printf("+%.*s+\n", OPT_LEN, BLANKSx150);
    // Пункты меню
    for (size_t i = 0; strlen(options[i]) != 0 && i < 100; i++)
        printf("| %*zu | %s\n", OPT_NUM_SIZE, i, options[i]);
    
    printf("+%.*s+\n", OPT_LEN, BLANKSx150);
}

void print_info(void)
{
    printf("\n\t* Программа предназначена для работы с частотным словарем\n \
\t* на основе двоичного дерева поиска. Словарь считывается из файла слов\n \
\t* Перечень доступных действий со стеком доступен в меню программы.\n");
    printf("Автор программы: Равашдех Фадей ИУ7-35Б. \n\n");
}

int get_option(size_t *option)
{
    char opt_str[OPTION_LEN+1], *end = NULL;
    int rc = RC_OK;

    printf("Введите пункт меню: ");
    if ((rc = get_n_input(&opt_str[0], OPTION_LEN+1)))
        return rc;
    else
        *option = strtol(opt_str, &end, 10);
    if (end != NULL && *end == '\n')
        return RC_OK;
    *option = 0; 
    return RC_INCORRECT_OPTION;
}

void print_error_msg(int rc)
{
    switch (rc)
    {
        case RC_OK:
            break;
        case RC_ALLOCATION_FAILED:
            printf("Ошибка: Ошибка выделения памяти.\n");
            break;
        case RC_INCORRECT_OPTION:
            printf("Ошибка: Действие с введенным пунктом отсутствует.\n");
            break;
        case RC_INPUT_ERROR_EOF:
            printf("Ошибка: Введен символ окончания ввода EOF.\n");
            printf("Завершение программы.\n");
            exit(RC_INPUT_ERROR_EOF);
            break;
        case RC_INCORRECT_INPUT:
            printf("Ошибка: Некорректный ввод.\n");
            break;
        case RC_EMPTY_STR:
            printf("Ошибка: пустая строка.\n");
            break;
        case RC_INCORRECT_FILE:
            printf("Ошибка: некорректный файл.\n");
            break;
        default:
            printf("Неизвестная ошибка номер %d\n", rc);
    }
}

int print_error(int rc)
{
    print_error_msg(rc);
    return rc;
}