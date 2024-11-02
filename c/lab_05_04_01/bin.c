#include "bin.h"

/**
 * @brief Считает размер бинарного файла
 * 
 * @param f файловая переменная
 * @param size размер файла
 * @return int код выхода
 */
int bin_file_size(FILE *f, size_t *size)
{
    long sz;
    long start_pos;

    start_pos = ftell(f);
    if (start_pos < 0)
        start_pos = 0;

    if (fseek(f, 0L, SEEK_END))
        return EXIT_CODE_INCORRECT_SIZE;

    sz = ftell(f);
    if (sz < 0)
        return EXIT_CODE_INCORRECT_SIZE;

    *size = sz;

    return fseek(f, start_pos, SEEK_SET);
}

/**
 * @brief Получение структуры студента из бинарного файла по его позиции
 * 
 * @param f файловая переменная
 * @param pos позиция целого числа в файле 
 * @param num целое число
 * @return int код выхода
 */
int get_student_by_pos(FILE *f, size_t pos, struct student *stud)
{
    long start_pos;

    start_pos = ftell(f);
    if (start_pos < 0)
        start_pos = 0;

    if (fseek(f, pos * sizeof(struct student), SEEK_SET))
        return EXIT_CODE_INCORRECT_SIZE;

    fread(stud, sizeof(struct student), 1, f);

    return fseek(f, start_pos, SEEK_SET);
}

/**
 * @brief Запись структуры студента в бинарный файл в заданную позицию
 * 
 * @param f файловая переменная
 * @param pos позиция целого числа в файле 
 * @param num целое число
 * @return int код выхода
 */
int put_student_by_pos(FILE *f, size_t pos, struct student *stud)
{
    long start_pos;

    start_pos = ftell(f);
    if (start_pos < 0)
        start_pos = 0;

    if (fseek(f, pos * sizeof(struct student), SEEK_SET))
        return EXIT_CODE_INCORRECT_SIZE;

    fwrite(stud, sizeof(struct student), 1, f);

    return fseek(f, start_pos, SEEK_SET);
}