#ifndef COMPARE_H__
#define COMPARE_H__

#include "consts.h"
#include "funcs.h"

#include <stddef.h>
#include <sys/time.h>
#include <stdio.h>

int compare(char *filename, size_t c2restr);

int compare_restr(char *filename, hto_t *hto_table, htc_t *htc_table, size_t c2restr);

#endif
