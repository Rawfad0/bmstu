#include "edges.h"


static void free_edges_arr(edges_t &edges)
{
    free(edges.edges_arr);
}

void set_edges_default(edges_t &edges)
{
    edges.edges_arr = NULL;
    edges.size = 0;
}

void clear_edges(edges_t &edges)
{
    free_edges_arr(edges);
    set_edges_default(edges);
}

static rc_t allocate_edges(edge_t **edges_arr, const int &size)
{
    if (size <= 0)
        return RC_EDGES_SIZE_ERROR;
    
    rc_t rc = RC_OK;

    edge_t *tmp_arr = (edge_t *) malloc(size * sizeof(edge_t));
    if (tmp_arr == NULL)
        rc = RC_MEMORY_ALLOCATION_ERROR;
    else
        *edges_arr = tmp_arr;
    
    return rc;
}

static rc_t file_read_edge(edge_t &edge, FILE *file_in)
{
    if (file_in == NULL)
        return RC_FILE_OPEN_ERROR;
    
    rc_t rc = RC_OK;
    edge_t tmp_edge = {0, 0};
    if (fscanf(file_in, "%d %d", &tmp_edge.p1, &tmp_edge.p2) != 2)
        rc = RC_FILE_READ_ERROR;
    else
    {
        edge.p1 = tmp_edge.p1;
        edge.p2 = tmp_edge.p2;
    }

    return rc;
}

static rc_t file_read_edges_size(int &size, FILE *file_in)
{
    if (file_in == NULL)
        return RC_FILE_OPEN_ERROR;
    
    rc_t rc = RC_OK;
    int tmp_size;

    if (fscanf_s(file_in, "%d", &tmp_size) != 1)
        rc = RC_FILE_READ_ERROR;
    else
        if (tmp_size <= 0)
            rc = RC_EDGES_SIZE_ERROR;
        else
            size = tmp_size;

    return rc;
}

rc_t file_read_edges_section(edges_t &edges, FILE *file_in)
{
    if (file_in == NULL)
        return RC_FILE_OPEN_ERROR;

    rc_t rc = RC_OK;
    edges_t tmp_edges = {NULL, 0};
    
    rc = file_read_edges_size(tmp_edges.size, file_in);
    if (rc == RC_OK)
    {
        rc = allocate_edges(&tmp_edges.edges_arr, tmp_edges.size);
        if (rc == RC_OK)
        {
            for (int i = 0; rc == RC_OK && i < tmp_edges.size; i++)
                rc = file_read_edge(tmp_edges.edges_arr[i], file_in);
            if (rc == RC_OK)
            {
                free(edges.edges_arr);
                edges.edges_arr = tmp_edges.edges_arr;
                edges.size = tmp_edges.size;
            }
            else
                free(tmp_edges.edges_arr);
        }
    }
    return rc;
}

// rc_t file_read_edges(edges_t &edges, FILE *file_in)
// {
//     if (file_in == NULL)
//         return RC_FILE_OPEN_ERROR;
    
//     rc_t rc = RC_OK;
//     rc = check_edges_fields(edges.edges_arr, edges.size);
//     if (rc == RC_OK)
//         for (int i = 0; rc == RC_OK && i < edges.size; i++)
//             rc = file_read_edge(edges.edges_arr[i], file_in);
    
//     return rc;
// }

// rc_t file_read_edges_arr(edges_t &edges, FILE *file_in)
// {
//     rc_t rc = RC_OK;

//     if (file_in == NULL)
//         rc = RC_FILE_OPEN_ERROR;
//     else
//     {
//         rc = allocate_edges(edges);
//         if (rc == RC_OK)
//         {
//             rc = file_read_edges(edges, file_in);
//             if (rc != RC_OK)
//                 clear_edges(edges);
//         }
//     }
//     return rc;
// }

// rc_t file_read_edges_section(edges_t &edges, FILE *file_in)
// {
//     if (file_in == NULL)
//         return RC_FILE_OPEN_ERROR;

//     rc_t rc = RC_OK;

//     rc = file_read_edges_num(edges, file_in);
//     if (rc == RC_OK)
//         file_read_edges_arr(edges, file_in);

//     return rc;
// }

static rc_t file_write_edges_num(const int size, FILE *file_out)
{
    if (size <= 0)
        return RC_EDGES_SIZE_ERROR;
    
    rc_t rc = RC_OK;

    if (fprintf(file_out, "%d\n", size) < 0)
        rc = RC_FILE_WRITE_ERROR;
    
    return rc;
}

static rc_t file_write_edge(const edge_t &edge, FILE *file_out)
{
    if (file_out == NULL)
        return RC_FILE_OPEN_ERROR;
    
    rc_t rc = RC_OK;

    if (fprintf(file_out, "%d %d\n", edge.p1, edge.p2) < 0)
        rc = RC_FILE_WRITE_ERROR;

    return rc;
}

rc_t file_write_edges_section(const edges_t &edges, FILE *file_out)
{
    if (edges.edges_arr == NULL)
        return RC_INCORRECT_EDGES;
    else if (edges.size <= 0)
        return RC_EDGES_SIZE_ERROR;

    rc_t rc = RC_OK;
    
    rc = file_write_edges_num(edges.size, file_out);
    if (rc == RC_OK)
        for (int i = 0; rc == RC_OK && i < edges.size; i++)
            rc = file_write_edge(edges.edges_arr[i], file_out);

    return rc;
}
