/**
 * Модуль содержащий функцию фильтр 
 */ 

#ifndef __KEY__H__
#define __KEY__H__

// Директивы препроцессора
#include "consts.h"
#include <string.h>
#include <stdlib.h>

// Объявления функций
int get_new_arr_size(const int *pb_src, const int *pe_src, int **pb, int **pe);

int key(const int *pb_src, const int *pe_src, int *pb_dst);

#endif