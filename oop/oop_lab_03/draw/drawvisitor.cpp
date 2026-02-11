#define _USE_MATH_DEFINES
#include "drawvisitor.h"
#include "../object/camera/camera.h"
#include "../object/carcas/carcas.h"
#include <iostream>

DrawVisitor::DrawVisitor() {}

#include <cmath>

static double dotproduct(const Point &left, const Point &right)
{
    return left.get_x() * right.get_x() + left.get_y() * right.get_y() + left.get_z() * right.get_z();
}

Point DrawVisitor::get_proection(const Point &point)
{
    Point copy = point;
    Point center = camera->center;
    Point right = camera->right;
    Point up = camera->up;
    Point forward = camera->forward;

    copy.move(center.get_x(), -center.get_y(), center.get_z());

    float length = sqrt(copy.get_x() * copy.get_x() + copy.get_y() * copy.get_y() + copy.get_z() * copy.get_z());
    if (fabs(length) > 0.001)
    {
        copy.set_x(copy.get_x() / length);
        copy.set_y(copy.get_y() / length);
        copy.set_z(copy.get_z() / length);
    }

    copy.move(-center.get_x(), -center.get_y(), -center.get_z());

    float fov = 120.0;
    float aspect_ratio = 1200.0 / 800.0;
    float near_plane = 0.1;
    float far_plane = 100.0;

    float top = tan((fov / 2) * M_PI / 180.0) * near_plane;
    float right_plane = top * aspect_ratio;

    // Преобразование координат в пространство камеры
    float dx = dotproduct(copy, right);
    float dy = dotproduct(copy, up);
    float dz = dotproduct(copy, forward);
    dx /= right_plane;
    dy /= top;
    dz = dz / (far_plane - near_plane) * (far_plane + near_plane) - (2 * near_plane * far_plane) / (far_plane - near_plane);

    copy.set_x(dx);
    copy.set_y(dy);
    copy.set_z(dz);

    copy.move(center.get_x(), center.get_y(), center.get_z());

    // Преобразование координат в экранное пространство
    copy.set_x((copy.get_x() + 1) * 1200 / 2);
    copy.set_y((1 - copy.get_y()) * 800 / 2);

    return copy;
}


void DrawVisitor::get_line_proection(Point &A, Point &B)
{
    return;
}
