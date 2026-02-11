#ifndef ACTION_STRUCTS_H
#define ACTION_STRUCTS_H

// Смещения по x, y, z
struct move
{
    double dx;
    double dy;
    double dz;
};
using move_t = struct move;

// Углы поворота вокруг осей OX, OY, OZ
struct rotate
{
    double ax;
    double ay;
    double az;
};
using rotate_t = struct rotate;

// Масштабирование по осям OX, OY, OZ
struct scale
{
    double kx;
    double ky;
    double kz;
};
using scale_t = struct scale;

#endif
