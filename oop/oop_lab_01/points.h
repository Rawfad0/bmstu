#ifndef POINTS_H
#define POINTS_H

#include <cstdio>
#include <cstdlib>

#include "point.h"
#include "errors.h"

struct points
{
    point_t *points_arr;
    int size;
};
using points_t = struct points;

void set_points_default(points_t &points);

void clear_points(points_t &points);

rc_t file_read_points_section(points_t &points, FILE *file_in);

rc_t file_write_points_section(const points_t &points, FILE *file_out);

rc_t move_points(points_t &points, const move_t &move);

rc_t rotate_points(points_t &points, const rotate_t &rotate);

rc_t scale_points(points_t &points, const scale_t &scale);

#endif
