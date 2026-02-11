#ifndef POINT_H
#define POINT_H

#include <cstdio>

#include "action_structs.h"
#include "errors.h"

struct point
{
    double x;
    double y;
    double z;
};
using point_t = struct point;

rc_t file_read_point(point_t &point, FILE *file_in);

rc_t file_write_point(const point_t &point, FILE *file_out);

void move_point(point_t &point, const move_t &move);

void rotate_point(point_t &point, const rotate_t &rotate);

void scale_point(point_t &point, const scale_t &scale);

#endif
