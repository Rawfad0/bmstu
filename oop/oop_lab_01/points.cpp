#include "points.h"


static void free_points_arr(points_t &points)
{
    free(points.points_arr);
}

void set_points_default(points_t &points)
{
    points.points_arr = NULL;
    points.size = 0;
}

void clear_points(points_t &points)
{
    free_points_arr(points);
    set_points_default(points);
}

static rc_t allocate_points(point_t **points_arr, const int &size)
{
    if (size <= 0)
        return RC_POINTS_SIZE_ERROR;

    rc_t rc = RC_OK;
    
    point_t *tmp_arr = (point_t *) malloc(size * sizeof(point_t));
    if (tmp_arr == NULL)
        rc = RC_MEMORY_ALLOCATION_ERROR;
    else
        *points_arr = tmp_arr;
    
    return rc;
}

static rc_t file_read_points_arr_size(int &size, FILE *file_in)
{
    if (file_in == NULL)
        return RC_FILE_OPEN_ERROR;
    
    rc_t rc = RC_OK;
    int tmp_size;
    if (fscanf_s(file_in, "%d", &tmp_size) != 1)
        rc = RC_FILE_READ_ERROR;
    else
        if (tmp_size <= 0)
            rc = RC_POINTS_SIZE_ERROR;
        else
            size = tmp_size;

    return rc;
}

rc_t file_read_points_section(points_t &points, FILE *file_in)
{
    if (file_in == NULL)
        return RC_FILE_OPEN_ERROR;

    rc_t rc = RC_OK;
    points_t tmp_points = {NULL, 0};
    
    rc = file_read_points_arr_size(tmp_points.size, file_in);
    if (rc == RC_OK)
    {
        rc = allocate_points(&tmp_points.points_arr, tmp_points.size);
        if (rc == RC_OK)
        {
            for (int i = 0; rc == RC_OK && i < tmp_points.size; i++)
                rc = file_read_point(tmp_points.points_arr[i], file_in);
            if (rc == RC_OK)
            {
                free(points.points_arr);
                points.points_arr = tmp_points.points_arr;
                points.size = tmp_points.size;
            }
            else
                free(tmp_points.points_arr);
        }
    }
    return rc;
}

static rc_t file_write_points_num(const int size, FILE *file_out)
{
    if (size <= 0)
        return RC_POINTS_SIZE_ERROR;
    
    rc_t rc = RC_OK;
    if (fprintf(file_out, "%d\n", size) < 0)
        rc = RC_FILE_WRITE_ERROR;
    return rc;
}

rc_t file_write_points_section(const points_t &points, FILE *file_out)
{
    if (points.points_arr == NULL)
        return RC_INCORRECT_POINTS;
    else if (points.size <= 0)
        return RC_POINTS_SIZE_ERROR;
    else if (file_out == NULL)
        return RC_FILE_OPEN_ERROR;
    
    rc_t rc = RC_OK;

    rc = file_write_points_num(points.size, file_out);
    if (rc == RC_OK)
        for (int i = 0; rc == RC_OK && i < points.size; i++)
            rc = file_write_point(points.points_arr[i], file_out);

    return rc;
}

rc_t move_points(points_t &points, const move_t &move)
{
    if (points.points_arr == NULL)
        return RC_INCORRECT_POINTS;
    else if (points.size <= 0)
        return RC_POINTS_SIZE_ERROR;

    for (int i = 0; i < points.size; i++)
        move_point(points.points_arr[i], move);

    return RC_OK;
}

rc_t rotate_points(points_t &points, const rotate_t &rotate)
{
    if (points.points_arr == NULL)
        return RC_INCORRECT_POINTS;
    else if (points.size <= 0)
        return RC_POINTS_SIZE_ERROR;

    for (int i = 0; i < points.size; i++)
        rotate_point(points.points_arr[i], rotate);
    
    return RC_OK;
}

rc_t scale_points(points_t &points, const scale_t &scale)
{
    if (points.points_arr == NULL)
        return RC_INCORRECT_POINTS;
    else if (points.size <= 0)
        return RC_POINTS_SIZE_ERROR;
    else if (scale.kx == 0 || scale.ky == 0 || scale.kz == 0)
        return RC_SCALE_COEFF_ERROR;
    
    for (int i = 0; i < points.size; i++)
        scale_point(points.points_arr[i], scale);
    
    return RC_OK;
}
