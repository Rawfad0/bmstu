#ifndef __CONSTS__H__
#define __CONSTS__H__

// Размеры и форматирование вывода
#define MAX_OPT_N 100
#define OPT_LEN 134
#define OPT_NUM_SIZE 3
#define PADDING_10 10
#define PADDING_9 9
#define PADDING_4 4
#define CHAR_LEN 1
#define MAX_FIELD_LEN 25
#define BLANKSx25 "-------------------------"
#define BLANKSx150 "------------------------------------------------------------------------------------------------------------------------------------------------------"

// Различные числа
#define ARGC_COUNT 2
#define OPTION_LEN 2
#define SORT_REPEAT 1000

// Поля таблицы
#define TABLE_FIELDS 12
#define ADDRESS_FIELDS 5
#define ADDRESS_TYPES 3
#define ADDRESS_TYPE_HOUSE "house"
#define ADDRESS_TYPE_DORMITORY "dormitory"
#define ADDRESS_TYPE_RENTAL_PLACE "rental_place"
#define ADDRESS_TYPE_HOUSE_FIELDS 3
#define ADDRESS_TYPE_DORMITORY_FIELDS 2
#define ADDRESS_TYPE_RENTAL_PLACE_FIELDS 4
#define MAX_MASK_LEN 40

// Поля таблицы ключей
#define KEY_TABLE_FIELDS 2
#define PADDING_5 5

// Маски регулярных выражений
#define MASK_LAST_NAME "^[A-Z][a-z]{1,19}?$"
#define MASK_FIRST_NAME "^[A-Z][a-z]{1,11}$"
#define MASK_GROUP "^[A-Z]{1,3}[1-9][0-9]?-[1-9]{2}[A-Z]?$"
#define MASK_GENDER "^[mf]$"
#define MASK_AGE "^[1-9][0-9]{1,2}$"
#define MASK_GPA "^([2-4].[0-9]{1,2})||(5.0[0]?)$"
#define MASK_YEAR "^[0-9]{4}$"
#define MASK_ADDRESS_TYPE "^(house)||(dormitory)||(rental_place)$"
#define MASK_STREET "[A-z0-9]{1,20}"
#define MASK_1to3_DIGITS "^[1-9][0-9]{0,2}$"
#define MASK_1to4_DIGITS "^[1-9][0-9]{0,3}$"
#define MASK_1to6_DIGITS "^[1-9][0-9]{0,5}$"
#define MASK_BLANK "^-$"
#define MASK_DATE "^[0-9]{2}.[0-9]{2}.[0-9]{4}$"

// Действие
#define OPT_PRINT_INFO 1
#define OPT_PRINT_TABLE 2
#define OPT_PRINT_STUD_ENROLL_YEAR_RENT 3
#define OPT_ADD_STUDENT 4
#define OPT_DEL_STUD_BY_LASTNAME 5
#define OPT_DEL_STUDS_BY_LASTNAME 6
#define OPT_PRINT_SORTED_KEY_TABLE 7
#define OPT_PRINT_SORTED_TABLE 8
#define OPT_PRINT_SORTED_TABLE_USING_KEY_TABLE 9
#define OPT_PRINT_COMPARISON 10
#define OPT_EXIT 11
#define OPT_SAVE_AND_EXIT 12

// RETURN CODES - Коды возврата
#define RC_OK 0
#define RC_INCORRECT_ARGC_COUNT 53
#define RC_INCORRECT_FILE 1
#define RC_INCORRECT_OPTION 2
#define RC_INPUT_ERROR 3
#define RC_INCORRECT_RECORD 4
#define RC_INCORRECT_FIELD 5
#define RC_INCORRECT_ADDRESS_TYPE 6
#define RC_INCORRECT_INPUT 7
#define RC_TABLE_IS_FULL 8
#define RC_WRITE_ERROR 9
#define RC_INCORRECT_DATE 10

#endif
