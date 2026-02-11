#ifndef EDGES_H
#define EDGES_H

#include <cstdio>
#include <cstdlib>

#include "points.h"
#include "errors.h"

struct edge
{
    int p1;
    int p2;
};
using edge_t = struct edge;

struct edges
{
    edge_t *edges_arr;
    int size;
};
using edges_t = struct edges;

void set_edges_default(edges_t &edges);

void clear_edges(edges_t &edges);

rc_t file_read_edges_section(edges_t &edges, FILE *file_in);

rc_t file_write_edges_section(const edges_t &edges, FILE *file_in);

#endif
