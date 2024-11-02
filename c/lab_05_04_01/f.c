#include "f.h"

/**
 * @brief Сравнение фамилий и имен
 * 
 * @param stud1 первый сравниваемый студент
 * @param stud2 второй сравниваемый студент
 * @return int код выхода
 */
int name_compare(struct student stud1, struct student stud2)
{
    int cmp = strcmp(stud1.last_name, stud2.last_name);
    if (cmp == 0)
        return strcmp(stud1.first_name, stud2.first_name);
    return cmp;
}

/**
 * @brief Средняя оценка
 * 
 * @param stud студент
 * @return double средняя оценка
 */
double grade_average(struct student stud)
{
    double sum = 0;

    for (size_t i = 0; i < GRADES_NUMBER; i++)
        sum += stud.grades[i];
    return sum / GRADES_NUMBER;
}

/**
 * @brief Нахождение студентов по префиксу фамилии
 * 
 * @param f1 файловая переменная ввода
 * @param f2 файловая переменная вывода
 * @param prefix префикс - начальная подстрока фамилии
 * @return int код выхода
 */
int find_stud_bin_file(FILE *f1, FILE *f2, char *prefix)
{
    size_t size;
    size_t prefix_size;
    struct student stud;
    size_t counter = 0;
    int r;

    r = bin_file_size(f1, &size);
    if (r != 0 || size % sizeof(struct student) != 0 || size == 0)
        return EXIT_CODE_INCORRECT_SIZE;

    prefix_size = strlen(prefix);
    for (size_t i = 0; i < size / sizeof(struct student); i++)
    {
        if (r = fread(&stud, sizeof(struct student), 1, f1), r != 1)
            return EXIT_CODE_INCORRECT_FILE;
        if (strlen(stud.last_name) > LAST_NAME_MAX || strlen(stud.last_name) == 0 
            || strlen(stud.first_name) > FIRST_NAME_MAX || strlen(stud.first_name) == 0)
            return EXIT_CODE_INCORRECT_ARRAY_SIZE;
        if (strncmp(stud.last_name, prefix, prefix_size) == 0)
        {
            if (r = fwrite(&stud, sizeof(struct student), 1, f2), r != 1)
                return EXIT_CODE_INCORRECT_FILE;
            counter++;
        }
    }
    if (counter == 0)
        return EXIT_CODE_STUDENT_NOT_FOUND;
    return 0;
}

/**
 * @brief удаление студентов со средним баллом ниже среднего по файлу
 * 
 * @param f файловая переменная
 * @param new_size размер получившегося файла
 * @return int код выхода
 */
int del_stud_bin_file(FILE *f, size_t *new_size)
{
    size_t size;
    struct student stud;
    double sum = 0;
    double mean;
    size_t shift = 0;
    int r;

    r = bin_file_size(f, &size);
    if (r != 0 || size % sizeof(struct student) != 0 || size == 0)
        return EXIT_CODE_INCORRECT_SIZE;

    for (size_t i = 0; i < size / sizeof(struct student); i++)
    {
        if (r = get_student_by_pos(f, i, &stud), r != 0)
            return r;
        sum += grade_average(stud);
    }
    mean = sum / (size / sizeof(struct student));

    for (size_t i = 0; i < size / sizeof(struct student); i++)
    {
        if (r = get_student_by_pos(f, i, &stud), r != 0)
            return r;
        if (grade_average(stud) < mean)
        {
            shift++;
            continue;
        }
        if (shift > 0)
            if (r = put_student_by_pos(f, i - shift, &stud), r != 0)
                return r;
    }

    *new_size = size - shift * sizeof(struct student);
    return 0;
}

/**
 * @brief Сортировка студентов по полному имени
 * 
 * @param f файловая переменная
 * @return int код выхода
 */
int sort_stud_bin_file(FILE *f)
{
    size_t size;
    size_t min_i;
    struct student stud1, stud2;
    int r;

    r = bin_file_size(f, &size);
    if (r != 0 || size % sizeof(struct student) != 0 || size == 0)
        return EXIT_CODE_INCORRECT_SIZE;

    for (size_t i = 0; i < size / sizeof(struct student); i++)
    {
        min_i = i;
        for (size_t j = i + 1; j < size / sizeof(struct student); j++)
        {
            if (r = get_student_by_pos(f, j, &stud1), r != 0)
                return r;
            if (r = get_student_by_pos(f, min_i, &stud2), r != 0)
                return r;

            if (name_compare(stud1, stud2) < 0)
                min_i = j;
        }

        if (min_i != i)
        {
            if (r = get_student_by_pos(f, min_i, &stud1), r != 0)
                return r;
            if (r = get_student_by_pos(f, i, &stud2), r != 0)
                return r;
            if (r = put_student_by_pos(f, min_i, &stud2), r != 0)
                return r;
            if (r = put_student_by_pos(f, i, &stud1), r != 0)
                return r;
        }
    }
    return 0;
}
