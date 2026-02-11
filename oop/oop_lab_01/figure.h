#ifndef FIGURE_H
#define FIGURE_H

#include <cstdio>

#include "points.h"
#include "edges.h"
#include "action_structs.h"
#include "errors.h"

struct figure
{
    points_t points;
    edges_t edges;
};

using figure_t = struct figure;

figure_t figure_init(void);

void free_figure(figure_t &figure);

rc_t file_read_figure(figure_t &figure, const char *filename);

rc_t file_write_figure(const figure_t &figure, const char *filename);

rc_t move_figure(figure_t &figure, const move_t &move);

rc_t rotate_figure(figure_t &figure, const rotate_t &rotate);

rc_t scale_figure(figure_t &figure, const scale_t &scale);

#endif
