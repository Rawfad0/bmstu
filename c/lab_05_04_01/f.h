/**
 * Модуль для основных вычислений программы
 */ 

#ifndef __F__H__
#define __F__H__

// Директивы препроцессора
#include "consts.h"
#include "bin.h"
#include "structs.h"
#include "io.h"
#include <stdio.h>
#include <string.h>

// Объявления функций
int sort_stud_bin_file(FILE *f);

int find_stud_bin_file(FILE *f1, FILE *f2, char *prefix);

int del_stud_bin_file(FILE *f, size_t *new_size);

#endif
