#include "io.h"

int read_matrix(char *filename, matrix_t *matrix)
{
    size_t counter;
    int rc = RC_OK;

    FILE *f = fopen(filename, "r");
    if (!f)
        rc = RC_INCORRECT_FILE;
    else if (fscanf(f, "%zu %zu %zu\n", &matrix->n, &matrix->m, &counter) != 3)
        rc = RC_INCORRECT_FILE_INPUT;
    else if (matrix->n * matrix->m < counter)
        rc = RC_INCORRECT_COUNTER;
    else if ((matrix->matrix = allocate_matrix(matrix->n, matrix->m)) == NULL)
        rc = RC_ALLOCATION_FAILED;
    else
    {
        size_t x, y;
        int value;
        while (rc == RC_OK && counter > 0)
        {
            if (fscanf(f, "%zu %zu %d\n", &y, &x, &value) != 3)
                rc = RC_INCORRECT_FILE_INPUT;
            else if (y == 0 || y > matrix->n || x == 0 || x > matrix->m)
                rc = RC_INCORRECT_FILE_INPUT;
            else
                matrix->matrix[y - 1][x - 1] = value;
            counter--;
        }
    }
    if (f)
        fclose(f);
    return rc;
}

/**
 * @brief Очистка буфера ввода
 * 
 */
void clear_buff(void)
{
    while (getchar() != '\n')
        ;
}

int get_input(char pch[], size_t n)
{
    char str[n + 1];
    for (size_t i = 0; i < n + 1; i++)
        str[i] = '\0';
    if (fgets(str, n + 1, stdin) == NULL)
        return RC_INPUT_ERROR;
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

int get_field(char field[], size_t n, char field_name[], char mask[])
{
    int rc = RC_OK;
    printf("Введите %s (до %ld знаков): ", field_name, n - 1);    // Приглашение к вводу
    if ((rc = get_input(&field[0], n + 1)))
        return rc;
    if (field[strlen(field) - 1] == '\n')
        field[strlen(field) - 1] = '\0';            // Удаление символа переноса строки

    // Проверка введенного поля с помощью регулярного выражение
    regex_t regex;
    regcomp(&regex, mask, REG_EXTENDED);
    if (regexec(&regex, field, 0, NULL, 0) == REG_NOMATCH)
    {
        printf("Введенное поле %s '%s' не прошло проверку. Поле должно иметь вид '%s'.\n", 
            field_name, field, mask);
        return RC_INCORRECT_INPUT;
    }
    
    return RC_OK;
}

int input_matrix(matrix_t *matrix)
{
    char n_str[SIZE_LEN], m_str[SIZE_LEN], val_num_str[VAL_NUM_LEN];
    char *end = NULL;
    int rc = RC_OK; 

    if ((rc = get_field(n_str, SIZE_LEN, "количество строк", SIZE_MASK)));
    else if ((rc = get_field(m_str, SIZE_LEN, "количество столбцов", SIZE_MASK)));
    else if ((rc = get_field(val_num_str, VAL_NUM_LEN, "количество непустых элементов", VAL_NUM_MASK)));
    else 
    {
        matrix->n = strtol(n_str, &end, 10);
        matrix->m = strtol(m_str, &end, 10);
        size_t val_num = strtol(val_num_str, &end, 10);
        char y_str[SIZE_LEN], x_str[SIZE_LEN], value_str[VALUE_LEN];
        size_t y, x;
        int value;
        if (val_num > matrix->n * matrix->m)
            return RC_INCORRECT_COUNTER;
        if ((matrix->matrix = allocate_matrix(matrix->n, matrix->m)))
        for (size_t i = 0; i < val_num && rc == RC_OK; i++)
        {
            if ((rc = get_field(y_str, SIZE_LEN, "номер строки (отсчет с 1)", SIZE_MASK)));
            else if ((rc = get_field(x_str, SIZE_LEN, "номер столбца (отсчет с 1)", SIZE_MASK)));
            else if ((rc = get_field(value_str, VALUE_LEN, "значение элемента", VALUE_MASK)));
            else
            {
                y = strtol(y_str, &end, 10);
                x = strtol(x_str, &end, 10);
                value = strtol(value_str, &end, 10);
                if (y == 0 || y > matrix->n || x == 0 || x > matrix->m)
                    return RC_INCORRECT_FILE_INPUT;
                matrix->matrix[y - 1][x - 1] = value;
            }
        }
    }
    return rc;
}

void print_matrix_as_table(matrix_t matrix)
{
    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
            printf("%*d ", 6, matrix.matrix[i][j]);
        printf("\n");
    }
}

void print_matrix(matrix_t matrix)
{
    printf("Матрица:\n");
    size_t counter = 0;
    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            if (matrix.matrix[i][j] != 0)
                counter++;
    if (counter == 0)
        printf("Пустая матрица.\n");
    else if (matrix.n < PRINT_MAX_N && matrix.m < PRINT_MAX_M)
        print_matrix_as_table(matrix);
    else
        for (size_t i = 0; i < matrix.n; i++)
            for (size_t j = 0; j < matrix.m; j++)
                if (matrix.matrix[i][j] != 0)
                    printf("%*zu %*zu %*d \n", SIZE_PADDING, i+1,
                        SIZE_PADDING, j+1, VALUE_PADDING, matrix.matrix[i][j]);
}

void print_menu(void)
{
    char options[MAX_OPT_N][2*OPT_LEN] = {"Информация о программе",
        "Ввести первую матрицу",
        "Ввести вторую матрицу",
        "Вывести первую матрицу",
        "Вывести вторую матрицу",
        "Вывести результат сложения двух матриц стандартным алгоритмом",
        "Вывести результат сложения двух матриц алгоритмом для разреженных матриц",
        "Вывести результаты сравнения сложений матриц в стандартном виде и в виде разреженной матрицы",
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
    printf("\n\t* Программа предназначена для сложения разреженных и стандартных матриц.\n \
\t* Перечень доступных действий с матрицами доступен в меню программы.\n \
\t* Матрицы представлены в координатном виде. Первая строка имееет вид:\n \
\t* '<количество строк N> <количество столбцов M> <количество ненулевых элементов матрицы K>',\n \
\t* где количество строк и количество столбцов не превышает 1000 (0 < N <= 1000, 0 < M <= 1000), \n\
\t* а количество ненулевых элементов не превышает размера матрицы (0 <= K <= N*M), \n\
\t* Остальные строки (в количестве равном количеству ненулевых элементов) имеют вид: \n\
\t* '<номер строки элемента I> <номер столбца элемента J> <значение элемента V>',\n\
\t* где номер строки элемента не превышает количества строк (0 < I <= N),\n\
\t* номер столбца элемента не превышает количества столбцов (0 < J <= M),\n\
\t* значение элемента представляется в виде дроби и не равно нулю (V =/= 0).\n");
    printf("Автор программы: Равашдех Фадей ИУ7-35Б. \n\n");
}

int get_option(size_t *option)
{
    char opt_str[OPTION_LEN+1], *end = NULL;
    int rc = RC_OK;

    printf("Введите пункт меню: ");
    if ((rc = get_input(&opt_str[0], OPTION_LEN+1)))
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
        case RC_INCORRECT_ARG_COUNT:
            printf("Ошибка: Неверные аргументы командной строки.\n");
            printf("Команда вызывается из командной строки так:\n./app.exe [matrix1.txt] [matrix2.txt]\n");
            break;
        case RC_INCORRECT_FILE:
            printf("Ошибка: Файл не найден или программа не имеет прав на чтение.\n");
            break;
        case RC_INCORRECT_FILE_INPUT:
            printf("Ошибка: Некорректный ввод данных из файла.\n");
            break;
        case RC_INCORRECT_COUNTER:
            printf("Ошибка: Некорректное количество непустых элементов матрицы.\n");
            break;
        case RC_INCORRECT_SIZE:
            printf("Ошибка: Некорректный размер матриц. \n");
            printf("Складываемые матрицы должны быть равны по размеру.\n");
            break;
        case RC_ALLOCATION_FAILED:
            printf("Ошибка: Ошибка выделения памяти.\n");
            break;
        case RC_INCORRECT_OPTION:
            printf("Ошибка: Действие с введенным пунктом отсутствует.\n");
            break;
        case RC_INPUT_ERROR:
            printf("Ошибка: Введен символ окончания ввода EOF.\n");
            printf("Завершение программы.\n");
            exit(RC_INPUT_ERROR);
            break;
        case RC_INCORRECT_INPUT:
            printf("Ошибка: Некорректный ввод.\n");
            break;
        case RC_INVALID_MATRIX:
            printf("Ошибка: Матрица не прошла проверку на корректность.\n");
            break;
        default:
            printf("Неизвестная ошибка номер %d", rc);
    }
}

int print_error(int rc)
{
    print_error_msg(rc);
    return rc;
}