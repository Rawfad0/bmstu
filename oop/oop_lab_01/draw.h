#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

#include "figure.h"
#include "points.h"

struct drawview
{
    QGraphicsScene *scene;
    double width;
    double height;
};
using drawview_t = struct drawview;

struct line
{
    point_t p1; // первая точка
    point_t p2; // вторая точка
};
using line_t = struct line;

rc_t draw_figure(const figure_t &figure, drawview_t &view);

#endif
