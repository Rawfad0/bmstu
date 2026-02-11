#ifndef __IO__H__
#define __IO__H__

//
#include "consts.h"
#include "structs.h"
#include "arrays.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 
int is_file_exist(char *file_name);

void print_info(void);

int read_record(FILE *f, char fields[TABLE_FIELDS][MAX_FIELD_LEN+1]);

void print_table_header(void);

void print_record(student_t stud);

void print_key_table_header(void);

void print_key_record(student_key_t student_key);

void print_menu(void);

int get_input(char pch[], size_t n);

int get_option(size_t *option);

void print_error_msg(int rc);

int print_error(int rc);

#endif
