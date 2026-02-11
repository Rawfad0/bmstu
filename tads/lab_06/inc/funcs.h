#ifndef FUNCS_H__
#define FUNCS_H__

#include "consts.h"
#include "ui.h"
#include "bin_tree.h"

#include <stddef.h>

int read_freq_list(bin_tree_t *tree, char **filename);

void print_freq_list(bin_tree_t tree);

int find_in_freq_list(bin_tree_t *tree, char *filename);

int find_in_file(char *filename, char *str, int *res, int *cmp_count);

#endif
