#include "io.h"
#include "table.h"
#include "consts.h"
#include "structs.h"
#include <stdio.h>

int controller(int option, char *filename, student_table_t *table, student_key_table_t *key_table);

int check_args(int argc);

int main(int argc, char **argv)
{
    int rc = RC_OK;
    if ((rc = check_args(argc)))
        return print_error(rc);

    student_table_t table = { 0 };
    if ((rc = read_table(argv[1], &table)))
        print_error_msg(rc);
    else
        printf("Таблица студентов успешно прочитана из файла.\n");

    student_key_table_t key_table = { 0 };
    fill_student_key_table(table, &key_table);
    printf("Таблица ключей фамилий студентов заполнена.\n");

    strcpy(table.table[0].address.dormitory.dorm_num, "1234567890123456789012");

    size_t option = 0;
    while (option != OPT_EXIT)
    {
        print_menu();
        print_error((rc = get_option(&option)));    // Выбор пользователем пункта меню с последующей обработкой ошибок
        if (!rc && (rc = controller(option, argv[1], &table, &key_table)))
            print_error(rc);
        if (option == OPT_SAVE_AND_EXIT && rc == RC_OK)
            break;
    }
    return rc;
}

/**
 * @brief Проверка аргументов
 * 
 * @param argc 
 * @return int 
 */
int check_args(int argc)
{
    int rc = RC_OK;

    if (argc != ARGC_COUNT)
        return RC_INCORRECT_ARGC_COUNT;

    return rc;
}

/**
 * @brief Контроллер
 * 
 * @param option выбранный пользователем пункт меню
 * @param filename имя файла
 * @param table таблица
 * @param key_table таблица ключей
 * @return int код возврата
 */
int controller(int option, char *filename, student_table_t *table, student_key_table_t *key_table)
{
    int rc = RC_OK;

    switch (option)
    {
        case OPT_PRINT_INFO:
            print_info();
            break;
        case OPT_PRINT_TABLE:
            print_table(*table);
            break;
        case OPT_PRINT_STUD_ENROLL_YEAR_RENT:
            if ((rc = print_filtered_table(*table)))
                return rc;
            break;
        case OPT_ADD_STUDENT:
            if ((rc = add_record(table)))
                return rc;
            fill_student_key_table(*table, key_table);
            break;
        case OPT_DEL_STUD_BY_LASTNAME:
            if ((rc = del_record(table)))
                return rc;
            fill_student_key_table(*table, key_table);
            break;
        case OPT_DEL_STUDS_BY_LASTNAME:
            if ((rc = del_records(table)))
                return rc;
            fill_student_key_table(*table, key_table);
            break;
        case OPT_PRINT_SORTED_KEY_TABLE:
            sort_key_table_and_print(key_table);
            break;
        case OPT_PRINT_SORTED_TABLE:
            print_sorted_table(table);
            fill_student_key_table(*table, key_table);
            break;
        case OPT_PRINT_SORTED_TABLE_USING_KEY_TABLE:
            print_table_using_sorted_key_table(*table, key_table);
            break;
        case OPT_PRINT_COMPARISON:
            if ((rc = compare(filename)))
                return rc;
            break;
        case OPT_EXIT:
            printf("Завершение программы.\n");
            break;
        case OPT_SAVE_AND_EXIT:
            if ((rc = write_table(filename, *table)))
                return rc;
            printf("Сохранение завершено.\nЗавершение программы.\n");
            break;
        default:
            printf("Некорректный номер пункта меню. Действия не существует.\n");
            return RC_INCORRECT_OPTION;
            break;
    }
    return rc;
}
