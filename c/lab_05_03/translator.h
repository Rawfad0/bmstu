/**
 * Модуль для преобразования файлов из обычных в бинарные и наоборот.
 */ 

#ifndef __TRANSLATOR__H__
#define __TRANSLATOR__H__

// Директивы препроцессора
#include "consts.h"
#include "bin.h"
#include <stdio.h>

// Объявления функций
int binary_to_text(FILE *b, FILE *f);

int text_to_binary(FILE *b, FILE *f);

#endif
