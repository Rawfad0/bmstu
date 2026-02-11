#ifndef ACTIONS_H
#define ACTIONS_H

#include "figure.h"
#include "draw.h"
#include "errors.h"
#include "action_structs.h"

enum action
{
    READ,
    WRITE,
    DESTRUCT,
    DRAW,
    MOVE,
    ROTATE,
    SCALE
};

struct request
{
    enum action action;
    union
    {
        const char *filename;
        drawview_t view;
        rotate_t rotate;
        move_t move;
        scale_t scale;
    };
};
using request_t = struct request;

rc_t action_controller(request_t &request);

#endif
