#ifndef __STRUCTS__H__
#define __STRUCTS__H__

// Включения
#include "consts.h"
#include <stdlib.h>
#include <stdint.h>

// Длины строк
#define LAST_NAME_LEN 20
#define FIRST_NAME_LEN 12
#define GROUP_LEN 9
#define GENDER_LEN 1
#define AGE_LEN 3
#define GPA_LEN 4
#define YEAR_LEN 4
#define DATE_LEN 10
#define ADDRESS_TYPE_LEN 14
#define STREET_NAME_LEN 20
#define CHAR3 3
#define CHAR4 4
#define CHAR6 6

// 
#define MAX_TABLE_LEN 1000


// Тип жилья
typedef struct
{
    char street[STREET_NAME_LEN+1];
    char house_num[CHAR3+1];
    char flat_num[CHAR4+1];
} house_t;

typedef struct
{
    char dorm_num[CHAR3+1];
    char room_num[CHAR4+1];
} dormitory_t;

typedef struct
{
    char street[STREET_NAME_LEN+1];
    char house_num[CHAR3+1];
    char flat_num[CHAR4+1];
    char cost[CHAR6+1];
} rental_place_t;

// Адрес
typedef union
{
    house_t house;
    dormitory_t dormitory;
    rental_place_t rent;
} address_t;

// /* Группа
// ИУ7-35Б
// | | |||
// | | ||Квалификация
// | | |Номер группы (в потоке)
// | | Семестр
// | Номер кафедры (в факультете)
// Факультет */
// typedef struct
// {
//     char faculty[FACULTY_STR_LEN+1];
//     uint8_t department;
//     uint8_t semester;
//     uint8_t group;
//     char qualification;
// } group_t;

// Cтудент
typedef struct
{
    char last_name[LAST_NAME_LEN+1];        // Фамилия
    char first_name[FIRST_NAME_LEN+1];      // Имя
    char group[GROUP_LEN+1];                // Группа
    char gender;                            // Пол
    char age[AGE_LEN+1];                    // Возраст
    char gpa[GPA_LEN+1];                    // Средняя оценка за сессию
    char enrollment_date[DATE_LEN+1];       // Дата поступления
    char address_type[ADDRESS_TYPE_LEN+1];  // Тип адреса
    address_t address;                      // Вариативное поле адреса
} student_t;
// Фиксированные поля занимают 80 байт
// Вариативное поле address занимает 37 байт

// Таблица студентов
typedef struct
{
    student_t table[MAX_TABLE_LEN];
    size_t n;
} student_table_t;

// Ключ-фамилия и индекс студента
typedef struct
{
    char last_name[LAST_NAME_LEN+1];
    size_t index;
} student_key_t;

// Таблица ключей
typedef struct
{
    student_key_t key_table[MAX_TABLE_LEN];
    size_t n;
} student_key_table_t;

#endif
