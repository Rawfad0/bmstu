#ifndef __TABLE__H__
#define __TABLE__H__


#include "io.h"
#include "consts.h"
#include "structs.h"
#include "arrays.h"
#include "sorts.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <sys/time.h>

// Функции для работы с таблицами записей студентов
/**
 * @brief Считывание таблицы из файла
 * 
 * @param file_name имя файла
 * @param table таблица
 * @return int код возврата
 */
int read_table(char *file_name, student_table_t *table);

/**
 * @brief Вывести таблицу
 * 
 * @param table таблица
 */
void print_table(student_table_t table);

/**
 * @brief Поиск студентов определенного года поступления и живущих в съемном жилье
 * 
 * @param students таблица студентов
 * @return int код возврата
 */
int print_filtered_table(student_table_t table);

/**
 * @brief Добавить запись в таблицу
 * 
 * @param table таблица
 * @return int код возврата
 */
int add_record(student_table_t *table);

/**
 * @brief Удалить студента с введенной фамилией из таблицы
 * 
 * @param table таблица
 * @return int код возврата
 */
int del_record(student_table_t *table);

/**
 * @brief Удалить всех студентов с введенной фамилией из таблицы
 * 
 * @param table таблица
 * @return int код возврата
 */
int del_records(student_table_t *table);

/**
 * @brief Заполнение таблицы ключей
 * 
 * @param table таблица
 * @param key_table таблица ключей
 */
void fill_student_key_table(student_table_t table, student_key_table_t *key_table);

/**
 * @brief Вывод 
 * 
 * @param key_table таблица ключей
 */
void sort_key_table_and_print(student_key_table_t *key_table);

/**
 * @brief Вывод отсортированной таблицы
 * 
 * @param table таблица
 */
void print_sorted_table(student_table_t *table);

/**
 * @brief Вывод отсортированной таблицы используя таблицу ключей
 * 
 * @param table таблица
 * @param key_table таблица ключей
 */
void print_table_using_sorted_key_table(student_table_t table, student_key_table_t *key_table);

/**
 * @brief Сравнение функций сортировок и отсутствие/наличие таблицы ключей
 * 
 * @param filename имя файла
 * @return int код возврата
 */
int compare(char *filename);

/**
 * @brief Запись таблицы в файл
 * 
 * @param filename имя файла
 * @param table таблица
 * @return int код возврата
 */
int write_table(char *filename, student_table_t table);

#endif