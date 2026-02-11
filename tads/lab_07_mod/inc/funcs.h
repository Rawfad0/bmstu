#ifndef FUNCS_H__
#define FUNCS_H__

#include "consts.h"
#include "ui.h"
#include "bin_tree.h"
#include "avl_tree.h"

#include <stddef.h>

int read(bin_tree_t *bin_tree, avl_tree_t *avl_tree, char **filename);

void print(bin_tree_t bin_tree, avl_tree_t avl_tree);

int find(bin_tree_t *bin_tree, avl_tree_t *avl_tree, char *filename);

#endif
