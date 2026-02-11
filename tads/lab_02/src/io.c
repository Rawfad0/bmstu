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

/**
 * @brief Существует ли файл
 * 
 * @param file_name имя файла
 * @return int код возврата
 */
int is_file_exist(char *file_name)
{
    int rc = RC_OK;
    FILE *f = fopen(file_name, "r");
    
    if (f)
        fclose(f);
    else 
        return RC_INCORRECT_FILE;
    return rc;
}

/**
 * @brief Прочитать запись
 * 
 * @param f файловый дескриптор
 * @param fields поля записи
 * @return int код возврата
 */
int read_record(FILE *f, char fields[TABLE_FIELDS][MAX_FIELD_LEN+1])
{
    size_t r = 0;
    r = fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s %s\n", \
    fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], \
    fields[6], fields[7], fields[8], fields[9], fields[10], fields[11]);
    if (r != TABLE_FIELDS)
        return RC_INCORRECT_RECORD;
    return RC_OK;
}

/**
 * @brief Печать контура заголовка таблицы
 * 
 * @param fields поля
 */
void print_table_header_lines(char fields[TABLE_FIELDS+1][MAX_FIELD_LEN])
{
    for (size_t i = 0; i < TABLE_FIELDS + 1; i++)
        printf("+%.*s", (int) paddings[i], fields[i]);
    printf("+\n");
}

/**
 * @brief Печать заголовка таблицы
 * 
 * @param fields поля
 */
void print_table_header_formatter(char fields[TABLE_FIELDS+1][MAX_FIELD_LEN])
{
    for (size_t i = 0; i < TABLE_FIELDS + 1; i++)
        printf("|%-*s", (int) paddings[i], fields[i]);
    printf("|\n");
}

/**
 * @brief Печать заголовка таблицы
 * 
 */
void print_table_header(void)
{
    print_table_header_lines(blanks_13);
    print_table_header_formatter(table_fields);
    print_table_header_lines(blanks_13);
}

/**
 * @brief Вывод студента в табличном формате
 * 
 * @param stud студент
 */
void print_record(student_t stud)
{
    // Вывод статических полей
    printf("|%-*s|%-*s|%-*s|%-c|%-*s|%-*s|%-*s|%-*s|", \
        LAST_NAME_LEN, stud.last_name, FIRST_NAME_LEN, stud.first_name, \
        GROUP_LEN, stud.group, stud.gender, AGE_LEN, stud.age, GPA_LEN, stud.gpa, \
        DATE_LEN, stud.enrollment_date, ADDRESS_TYPE_LEN, stud.address_type);

    // Вывод вариативных полей
    if (!strcmp(stud.address_type, ADDRESS_TYPE_HOUSE))
        printf("%-*s|%-*s|%-*s|%-*s|\n", STREET_NAME_LEN, stud.address.house.street, \
            PADDING_10, stud.address.house.house_num, PADDING_9, stud.address.house.flat_num, CHAR6, "-");
    else if (!strcmp(stud.address_type, ADDRESS_TYPE_DORMITORY))
        printf("%-*s|%-*s|%-*s|%-*s|\n", STREET_NAME_LEN, "-", \
            PADDING_10, stud.address.dormitory.dorm_num, PADDING_9, stud.address.dormitory.room_num, CHAR6, "-");
    else if (!strcmp(stud.address_type, ADDRESS_TYPE_RENTAL_PLACE))
        printf("%-*s|%-*s|%-*s|%-*s|\n", STREET_NAME_LEN, stud.address.rent.street, \
            PADDING_10, stud.address.rent.house_num, PADDING_9, stud.address.rent.flat_num, CHAR6, stud.address.rent.cost);
}

/**
 * @brief Печать контура заголовка таблицы ключей
 * 
 * @param fields поля
 */
void print_key_table_header_lines(char fields[KEY_TABLE_FIELDS+1][MAX_FIELD_LEN])
{
    for (size_t i = 0; i < KEY_TABLE_FIELDS + 1; i++)
        printf("+%.*s", (int) key_table_paddings[i], fields[i]);
    printf("+\n");
}

/**
 * @brief Печать заголовка таблицы ключей
 * 
 * @param fields поля
 */
void print_key_table_header_formatter(char fields[KEY_TABLE_FIELDS+1][MAX_FIELD_LEN])
{
    for (size_t i = 0; i < KEY_TABLE_FIELDS + 1; i++)
        printf("|%-*s", (int) key_table_paddings[i], fields[i]);
    printf("|\n");
}

/**
 * @brief Печать заголовка таблицы ключей
 * 
 */
void print_key_table_header(void)
{
    print_key_table_header_lines(blanks_3);
    print_key_table_header_formatter(key_table_fields);
    print_key_table_header_lines(blanks_3);
}

/**
 * @brief Вывод ключа в табличном формате
 * 
 * @param stud_key запись таблицы ключей
 */
void print_key_record(student_key_t stud_key)
{
    printf("|%-*s|%*zu|\n", LAST_NAME_LEN, stud_key.last_name, PADDING_5, stud_key.index + 1);
}

/**
 * @brief Вывод меню программы
 * 
 */
void print_menu(void)
{
    char options[MAX_OPT_N][2*OPT_LEN] = {"Информация о программе",
        "Вывести общий список студентов",
        "Вывести список студентов, указанного года поступления, живущих в съемном жилье",
        "Добавить запись о студенте в конец таблицы",
        "Удалить запись о студенте из таблицы по фамилии",
        "Удалить запись о студентах из таблицы по фамилии",
        "Вывести отсортированную по фамилии студента таблицу ключей",
        "Вывести студентов упорядоченных по фамилии",
        "Вывести студентов упорядоченных по фамилии, используя таблицу ключей",
        "Вывести результаты сравнения эффективности работы программы при обработке данных в исходной таблице и таблице ключей",
        "Выйти",
        "Сохранить и выйти"};
    
    // Шапка меню
    printf("+%.*s+\n", OPT_LEN, BLANKSx150);
    printf("|%*sМЕНЮ%*s|\n", OPT_LEN/2 - 2, " ", OPT_LEN/2 - 2, " ");
    printf("+%.*s+\n", OPT_LEN, BLANKSx150);
    // Пункты меню
    for (size_t i = 0; strlen(options[i]) != 0 && i < 100; i++)
        printf("| %*zu | %s\n", OPT_NUM_SIZE, i + 1, options[i]);
    
    printf("+%.*s+\n", OPT_LEN, BLANKSx150);
}

/**
 * @brief Вывод информации о программе
 * 
 */
void print_info(void)
{
    printf("\n\t* Программа предназначена для работы с таблицей студентов. \n \
\t* Перечень доступных действий с таблицей доступен в меню программы.\n \
\t* Запись студента имеет вид: '<фамилия> <имя> <группа> <пол> <возраст> \n \
\t* <средний балл за сессию> <дата поступления> <адрес> <адрес 1> <адрес 2> <адрес 3> <адрес 4>'.\n\
\t* Где длина поля <фамилия> до 20 символов, длина поля <имя> до 12 символов; \n \
\t* поле <группа> имеет формат 'CсcDd-DDc', где С/c - буква/необяз. буква, D/d - цифра/необяз. цифра;\n\
\t* поле <пол> может принимать значения 'm' или 'f', длина поля <возраст> до 3 цифр; \n \
\t* поле <средний балл> имеет формат D.Dd, поле <дата поступления> - имеет формат DD.DD.DDDD;\n\
\t* поле <адрес> может принимать три типа значений, поля <адрес N> зависят от жилья студента:\n\
\t* 1. Дом. Поля: 'house <улица> <№дома> <№кв> -'. Где длина поля <улица> до 25 символов,\n\
\t* длина поля <№дома> до 3 цифр, длина поля <№кв> до 4 символов. \n \
\t* 2. Общежитие. Поля: 'dormitory - <№общ> <№комн> -'. Где длина поля <№общ> до 3 цифр,\n\
\t* длина поля <№комн> до 4 цифр. \n \
\t* 3. Съемное жилье. Поля: 'rental_place <улица> <№дома> <№кв> <стоимость>'. \n \
\t* Где длина поля <улица> до 20 символов, длина поля <№дома> до 3 цифр, \n \
\t* длина поля <№кв> до 4 символов, длина поля <стоимость> до 6 цифр. \n");
    printf("Автор программы: Равашдех Фадей ИУ7-35Б. \n\n");
}

/**
 * @brief Чтение строки определенной длины из стандартного потока ввода
 * 
 * @param pch указатель на принимаемую строку
 * @param n длина строки
 * @return int код возврата
 */
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

/**
 * @brief Получение выбранного пользователем пункта
 * 
 * @param option выбранный пункт
 * @return int код возврата
 */
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

/**
 * @brief Вывод сообщения, пояснящего ошибку
 * 
 * @param rc код возврата
 */
void print_error_msg(int rc)
{
    switch (rc)
    {
        case RC_OK:
            break;
        case RC_INCORRECT_ARGC_COUNT:
            printf("Ошибка: Неверные аргументы командной строки.\n");
            printf("Команда вызывается из командной строки так:\n./app.exe table_file.txt\n");
            break;
        case RC_INCORRECT_FILE:
            printf("Ошибка: Файл не найден или программа не имеет прав на чтение.\n");
            break;
        case RC_INCORRECT_OPTION:
            printf("Ошибка: Действие с введенным пунктом отсутствует.\n");
            break;
        case RC_INPUT_ERROR:
            printf("Ошибка: Введен символ окончания ввода EOF.\n");
            printf("Завершение программы.\n");
            exit(RC_INPUT_ERROR);
            break;
        case RC_INCORRECT_RECORD:
            printf("Ошибка: Прочитана запись из файла, содержащая неверное количество полей.\n");
            break;
        case RC_INCORRECT_FIELD:
            printf("Ошибка: Поле не прошло проверку формата.\n");
            break;
        case RC_INCORRECT_ADDRESS_TYPE:
            printf("Ошибка: Поле адреса не соответствует ни одному типу адреса.\n");
            break;
        case RC_INCORRECT_INPUT:
            printf("Ошибка: Некорректный ввод. Количество введенных символов равно нулю или превысило ожидаемое.\n");
            break;
        case RC_TABLE_IS_FULL:
            printf("Ошибка: Таблица заполнена, добавление записей невозможно.\n");
            break;
        case RC_INCORRECT_DATE:
            printf("Ошибка: Некорректная дата.\n");
            break;
        case RC_WRITE_ERROR:
            printf("Ошибка: Невозможно сохранить данные в файл. Возможно нет прав на запись.\n");
            break;
    }
}

/**
 * @brief Вывод сообщения, пояснящего ошибку, и возврат того же кода возврата
 * 
 * @param rc код возврата
 * @return int код возврата
 */
int print_error(int rc)
{
    print_error_msg(rc);
    return rc;
}