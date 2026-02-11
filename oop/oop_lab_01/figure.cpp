#include "figure.h"

figure_t figure_init(void)
{
    figure_t figure;

    set_points_default(figure.points);
    set_edges_default(figure.edges);

    return figure;
}

void free_figure(figure_t &figure)
{
    clear_points(figure.points);
    clear_edges(figure.edges);
}

static rc_t check_figure_fields(const points_t &points, const edges_t &edges)
{
    rc_t rc = RC_OK;

    if (points.points_arr == NULL || points.size <= 0 || edges.edges_arr == NULL || edges.size <= 0)
        rc = RC_INCORRECT_FIGURE;

    return rc;
}

static rc_t check_figure(const figure_t &figure)
{
    return check_figure_fields(figure.points, figure.edges);
}

static rc_t file_read_figure_data(figure_t &figure, FILE *file_in)
{
    if (file_in == NULL)
        return RC_FILE_OPEN_ERROR;
    
    rc_t rc = RC_OK;
    figure_t tmp_figure = figure_init();
    
    rc = file_read_points_section(tmp_figure.points, file_in);
    if (rc == RC_OK)
    {
        rc = file_read_edges_section(tmp_figure.edges, file_in);
        if (rc == RC_OK)
        {
            clear_points(figure.points);
            clear_edges(figure.edges);
            figure.points = tmp_figure.points;
            figure.edges = tmp_figure.edges;
        }
        else
            clear_points(tmp_figure.points);
    }

    return rc;
}

rc_t file_read_figure(figure_t &figure, const char *filename)
{
    if (filename == NULL)
        return RC_FILE_OPEN_ERROR;

    rc_t rc = RC_OK;
    
    FILE *file_in = fopen(filename, "r");
    if (file_in == NULL)
        rc = RC_FILE_OPEN_ERROR;
    else
    {
        figure_t tmp_figure = figure_init();

        rc = file_read_figure_data(tmp_figure, file_in); 
        if (rc == RC_OK)
        {
            free_figure(figure);
            figure = tmp_figure;
        }
        else
            free_figure(tmp_figure);
        fclose(file_in);
    }

    return rc;
}

static rc_t file_write_figure_data(const points_t &points, const edges_t &edges, FILE *file_out)
{
    if (file_out == NULL)
        return RC_FILE_WRITE_ERROR;

    rc_t rc = RC_OK;
    rc = check_figure_fields(points, edges);
    if (rc == RC_OK)
    {
        rc = file_write_points_section(points, file_out);
        if (rc == RC_OK)
            rc = file_write_edges_section(edges, file_out);
    }
    return rc;
}

rc_t file_write_figure(const figure_t &figure, const char *filename)
{
    if (filename == NULL)
        return RC_FILE_WRITE_ERROR;
    
    rc_t rc = RC_OK;

    rc = check_figure_fields(figure.points, figure.edges);
    if (rc == RC_OK)
    {
        FILE *file_out = fopen(filename, "w");
        if (file_out == NULL)
            rc = RC_FILE_WRITE_ERROR;
        else
        {
            rc = file_write_figure_data(figure.points, figure.edges, file_out);
            fclose(file_out);
        }
    }
    return rc;
}

rc_t move_figure(figure_t &figure, const move_t &move)
{
    rc_t rc = RC_OK;

    rc = check_figure_fields(figure.points, figure.edges);
    if (rc == RC_OK)
        rc = move_points(figure.points, move);
    
    return rc;
}

rc_t rotate_figure(figure_t &figure, const rotate_t &rotate)
{
    rc_t rc = RC_OK;

    rc = check_figure_fields(figure.points, figure.edges);
    if (rc == RC_OK)
        rc = rotate_points(figure.points, rotate);
    
    return rc;
}

rc_t scale_figure(figure_t &figure, const scale_t &scale)
{
    rc_t rc = RC_OK;

    rc = check_figure_fields(figure.points, figure.edges);
    if (rc == RC_OK)
        rc = scale_points(figure.points, scale);
    
    return rc;
}
