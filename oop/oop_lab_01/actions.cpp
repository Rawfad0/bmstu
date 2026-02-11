#include "actions.h"

rc_t action_controller(request_t &request)
{
    static figure_t figure = figure_init();

    rc_t rc = RC_OK;
    switch (request.action)
    {
        case READ:
            rc = file_read_figure(figure, request.filename);
            break;
        case WRITE:
            rc = file_write_figure(figure, request.filename);
            break;
        case DESTRUCT:
            free_figure(figure);
            break;
        case DRAW:
            rc = draw_figure(figure, request.view);
            break;
        case MOVE:
            rc = move_figure(figure, request.move);
            break;
        case ROTATE:
            rc = rotate_figure(figure, request.rotate);
            break;
        case SCALE:
            rc = scale_figure(figure, request.scale);
            break;
        default:
            rc = RC_UNDEFINED_ACTION;
    }

    return rc;
}
