/**
 * @file bin_tree.h
 * @brief Взвешенный граф
 * 
 */

#ifndef GRAPH_H__
#define GRAPH_H__

#include "matrix.h"
#include "ui.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

typedef struct graph *graph_t;

int graph_read(char **filename, graph_t *graph);

int graph_write(graph_t graph);

void d_wrapper(graph_t graph);

void fw_wrapper(graph_t graph);

void graph_del(graph_t *graph);

#endif
