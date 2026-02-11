#ifndef FUNCS_H__
#define FUNCS_H__

#include "consts.h"
#include "ui.h"
#include "bin_tree.h"
#include "hash_open.h"
#include "hash_closed.h"

#include <stddef.h>

int read(bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char **filename, size_t c2restr);

void print(hto_t hto_table, htc_t htc_table);

int find(char *filename, bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, size_t c2restr);

int remove_word(char *filename, bin_tree_t *tree, hto_t hto_table, htc_t htc_table, size_t c2restr);

int balance(bin_tree_t *tree);

int write(bin_tree_t tree);

int change_c2restr(size_t *c2restr, bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char *filename);

int read_file(bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char *filename, size_t c2restr);

#endif
