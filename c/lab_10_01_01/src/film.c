#include "film.h"

void free_film(film_t *film)
{ 
    free(film->title);
    free(film->name);
    free(film);
}

void free_film_list(node_t **head)
{
    while (*head != NULL)
        free_film(pop_front(head));
}

int compare_by_year(const void *p, const void *q)
{
    return ((film_t *) p)->year - ((film_t *) q)->year;
}

int read_film(FILE *f, film_t *film)
{
    int rc = RC_OK;
    size_t len = 0;
    int read;

    film->title = NULL;
    film->name = NULL;

    if ((read = getline(&film->title, &len, f)) == -1 || read <= 1)
        rc = RC_INCORRECT_INPUT;
    else if ((read = getline(&film->name, &len, f)) == -1 || read <= 1)
        rc = RC_INCORRECT_INPUT;
    else if (fscanf(f, "%d\n", &(film->year)) != 1 || film->year <= 0)
        rc = RC_INCORRECT_INPUT;
    else
    {
        if (film->title[strlen(film->title) - 1] == '\n')
            film->title[strlen(film->title) - 1] = '\0';
        if (film->name[strlen(film->name) - 1] == '\n')
            film->name[strlen(film->name) - 1] = '\0';
    }
    return rc;
}

int read_film_list(char *file_name, node_t **film_list)
{
    int rc = RC_OK;

    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        rc = RC_INCORRECT_FILE;
    else
    {
        while (!feof(f) && rc == RC_OK)
        {
            film_t *film = malloc(sizeof(film_t));
            node_t *node = NULL;
            if (film == NULL)
                rc = RC_ALLOCATION_FAILED;
            else if ((rc = read_film(f, film)))
                free_film(film);
            else if ((node = make_node(film)) == NULL)
                rc = RC_ALLOCATION_FAILED;
            else
                insert(film_list, node, *film_list);
        }
        fclose(f);
    }
    return rc;
}

int write_film_list(char *file_name, node_t *film_list)
{
    int rc = RC_OK;

    FILE *f = fopen(file_name, "w");
    if (f == NULL)
        rc = RC_INCORRECT_FILE;
    else
    {  
        node_t *node = film_list;
        film_t *film = NULL;
        while (node != NULL && rc == RC_OK)
        {
            film = get_data(node);
            fprintf(f, "%s\n%s\n%d\n", film->title, film->name, film->year);
            node = next_node(node);
        }
        fclose(f);
    }
    return rc;
}
