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
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif