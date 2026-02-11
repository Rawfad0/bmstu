#include "point.h"

#define _USE_MATH_DEFINES
#include <cmath>


rc_t file_read_point(point_t &point, FILE *file_in)
{
    if (file_in == NULL)
        return RC_FILE_OPEN_ERROR;
    
    rc_t rc = RC_OK;
    point_t tmp_point = {0, 0, 0};

    if(fscanf(file_in, "%lf %lf %lf", &tmp_point.x, &tmp_point.y, &tmp_point.z) != 3)
        rc = RC_FILE_READ_ERROR;
    else
    {
        point.x = tmp_point.x;
        point.y = tmp_point.y;
        point.z = tmp_point.z;
    }

    return rc;
}

rc_t file_write_point(const point_t &point, FILE *file_out)
{
    rc_t rc = RC_OK;
    if (file_out == NULL)
        rc = RC_FILE_OPEN_ERROR;
    else
        if (fprintf(file_out, "%lf %lf %lf\n", point.x, point.y, point.z) < 0)
            rc = RC_FILE_WRITE_ERROR;
    return rc;
}

static inline double to_radians(const double angle)
{
    return angle * M_PI / 180;
}

static void rotate_ox(point_t &point, const double angle)
{
    double radians = to_radians(angle);
    double r_cos = cos(radians);
    double r_sin = sin(radians);
    double y = point.y;

    point.y = point.y * r_cos + point.z * r_sin;
    point.z = -y * r_sin + point.z * r_cos;
}

static void rotate_oy(point_t &point, const double angle)
{
    double radians = to_radians(angle);
    double r_cos = cos(radians);
    double r_sin = sin(radians);
    double x = point.x;

    point.x = point.x * r_cos + point.z * r_sin;
    point.z = -x * r_sin + point.z * r_cos;
}

static void rotate_oz(point_t &point, const double angle)
{
    double radians = to_radians(angle);
    double r_cos = cos(radians);
    double r_sin = sin(radians);
    double x = point.x;

    point.x = point.x * r_cos + point.y * r_sin;
    point.y = -x * r_sin + point.y * r_cos;
}

void move_point(point_t &point, const move_t &move)
{
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}

void rotate_point(point_t &point, const rotate_t &rotate)
{
    rotate_ox(point, rotate.ax);
    rotate_oy(point, rotate.ay);
    rotate_oz(point, rotate.az);
}

void scale_point(point_t &point, const scale_t &scale)
{
    point.x = point.x * scale.kx;
    point.y = point.y * scale.ky;
    point.z = point.z * scale.kz;
}
