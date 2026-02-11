#include "draw.h"


static rc_t clear_scene(QGraphicsScene *scene)
{
    if (scene == NULL)
        return RC_INCORRECT_SCENE;
    
    scene->clear();

    return RC_OK;
}

static point_t view_converse_point(point_t point, const int width, const int height)
{
    point.x += width / 2;
    point.y += height / 2;

    return point;
}

static rc_t view_converse_line(point_t &p1, point_t &p2, const int width, const int height, const edge_t &edge, const point_t *point_arr, const int size)
{
    
    if (point_arr == NULL)
        return RC_INCORRECT_POINTS;
    else if (edge.p1 >= size || edge.p2 >= size)
        return RC_INCORRECT_EDGE;

    p1 = view_converse_point(point_arr[edge.p1], width, height);
    p2 = view_converse_point(point_arr[edge.p2], width, height);

    return RC_OK;
}

static rc_t draw_line(QGraphicsScene *scene, const point_t &p1, const point_t &p2)
{
    if (scene == NULL)
        return RC_INCORRECT_SCENE;

    scene->addLine(p1.x, p1.y, p2.x, p2.y);

    return RC_OK;
}

static rc_t draw_lines(const drawview_t &view, const points_t &points, const edges_t &edges)
{
    if (view.scene == NULL)
        return RC_INCORRECT_SCENE;
    else if (points.points_arr == NULL || edges.edges_arr == NULL)
        return RC_MEMORY_ALLOCATION_ERROR;

    rc_t rc = RC_OK;


    line_t line;
    for (int i = 0; rc == RC_OK && i < edges.size; i++)
    {
        rc = view_converse_line(line.p1, line.p2, view.width, view.height, edges.edges_arr[i], points.points_arr, points.size);
        if (rc == RC_OK)
            rc = draw_line(view.scene, line.p1, line.p2);
    }
    
    return rc;
}

rc_t draw_figure(const figure_t &figure, drawview_t &view)
{
    rc_t rc = RC_OK;
    
    rc = clear_scene(view.scene);
    if (rc == RC_OK)
        rc = draw_lines(view, figure.points, figure.edges);

    return rc;
}
