#include "ui.h"
#include "consts.h"
#include "graph.h"

#include <stdio.h>

int controller(int option, graph_t *graph, char **filename);

int main(void)
{
    int rc = RC_OK;

    graph_t graph = NULL;
    char *filename = NULL;

    size_t option = 0;
    while (option != OPT_EXIT)
    {
        print_menu();
        if ((rc = get_option(&option)))
            print_error(rc);    // Выбор пользователем пункта меню с последующей обработкой ошибок
        else if ((rc = controller(option, &graph, &filename)))
            print_error(rc);
    }
    graph_del(&graph);
    free(filename);

    return rc;
}

int controller(int option, graph_t *graph, char **filename)
{
    int rc = RC_OK;

    switch (option)
    {
        case OPT_PRINT_INFO:
            print_info();
            break;
        case OPT_READ:
            rc = graph_read(filename, graph);
            break;
        case OPT_D_ALG:
            d_wrapper(*graph);
            break;
        case OPT_FW_ALG:
            fw_wrapper(*graph);
            break;
        case OPT_WRITE:
            rc = graph_write(*graph);
            break;
        case OPT_EXIT:
            printf("Завершение программы.\n");
            break;
        default:
            printf("Некорректный номер пункта меню. Действия не существует.\n");
            return RC_INCORRECT_OPTION;
            break;
    }
    return rc;
}
