/**
 * Модуль для работы с бинарными файлами.
 */ 

#ifndef __BIN__H__
#define __BIN__H__

// Директивы препроцессора
#include "consts.h"
#include "structs.h"
#include <stdio.h>

// Объявления функций
int bin_file_size(FILE *f, size_t *size);

int get_student_by_pos(FILE *f, size_t pos, struct student *stud);

int put_student_by_pos(FILE *f, size_t pos, struct student *stud);

#endif
