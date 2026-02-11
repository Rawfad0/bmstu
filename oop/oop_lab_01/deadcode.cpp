#include "point.h"
#include "points.h"
#include "edges.h"
#include "figure.h"

void copy_point(point_t &dst_point, const point_t &src_point)
{
    dst_point.x = src_point.x;
    dst_point.y = src_point.y;
    dst_point.z = src_point.z;
}

rc_t deep_copy_points(points_t &dst_points, const points_t &src_points)
{
    if (src_points.points_arr == NULL)
        return RC_INCORRECT_POINTS;
    else if (src_points.size <= 0)
        return RC_POINTS_SIZE_ERROR;
    
    rc_t rc = RC_OK;
    points_t tmp_points = {NULL, 0};

    tmp_points.size = src_points.size;
    rc = allocate_points(&tmp_points.points_arr, src_points.size);
    if (rc == RC_OK)
    {
        for (int i = 0; i < src_points.size; i++)
            copy_point(tmp_points.points_arr[i], src_points.points_arr[i]);
        dst_points.points_arr = tmp_points.points_arr;
        dst_points.size = tmp_points.size;
    }
    else
        free(tmp_points.points_arr);

    return rc;
}

void copy_edge(edge_t &dst_edge, const edge_t &src_edge)
{
    dst_edge.p1 = src_edge.p1;
    dst_edge.p2 = src_edge.p2;
}

rc_t deep_copy_edges(edges_t &dst_edges, const edges_t &src_edges)
{
    if (src_edges.edges_arr == NULL)
        return RC_INCORRECT_POINTS;
    else if (src_edges.size <= 0)
        return RC_POINTS_SIZE_ERROR;
    
    rc_t rc = RC_OK;
    edges_t tmp_edges = {NULL, 0};

    tmp_edges.size = src_edges.size;
    rc = allocate_edges(&tmp_edges.edges_arr, src_edges.size);
    if (rc == RC_OK)
    {
        for (int i = 0; i < src_edges.size; i++)
            copy_edge(tmp_edges.edges_arr[i], src_edges.edges_arr[i]);
        dst_edges.edges_arr = tmp_edges.edges_arr;
        dst_edges.size = tmp_edges.size;
    }
    else
        free(tmp_edges.edges_arr);

    return rc;
}


rc_t deep_copy_figure(figure_t &dst_figure, const figure_t &src_figure)
{
    rc_t rc = RC_OK;
    
    rc = check_figure_fields(src_figure.points, src_figure.edges);
    if (rc == RC_OK)
    {
        figure_t tmp_figure = figure_init();

        rc = deep_copy_points(tmp_figure.points, src_figure.points);
        if (rc == RC_OK)
        {
            rc = deep_copy_edges(tmp_figure.edges, src_figure.edges);
            if (rc == RC_OK)
            {
                dst_figure.points = tmp_figure.points;
                dst_figure.edges = tmp_figure.edges;
            }
            else
            {
                clear_points(tmp_figure.points);
                clear_edges(tmp_figure.edges);
            }
        }
        else
            clear_points(tmp_figure.points);
    }
    
    return rc;
}

rc_t move_figure(figure_t &figure, const move_t &move)
{
    rc_t rc = check_figure_fields(figure.points, figure.edges);
    if (rc == RC_OK)
    {
        figure_t tmp_figure;
        rc = deep_copy_figure(tmp_figure, figure);
        if (rc == RC_OK)
        {
            rc = move_points(tmp_figure.points, move);
            if (rc == RC_OK)
            {
                clear_points(figure.points);
                clear_edges(figure.edges);
                figure.points = tmp_figure.points;
                figure.edges = tmp_figure.edges;
            }
            else
            {
                clear_points(tmp_figure.points);
                clear_edges(tmp_figure.edges);
            }
        }        
    }
    return rc;
}
