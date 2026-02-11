#include "ui.h"
#include "consts.h"
#include "bin_tree.h"
#include "avl_tree.h"
#include "funcs.h"
// #include "compare.h"

#include <stdio.h>

int controller(int option, bin_tree_t *bin_tree, avl_tree_t *avl_tree, char **filename);

int main(void)
{
    int rc = RC_OK;

    bin_tree_t bin_tree = NULL;
    avl_tree_t avl_tree = NULL;
    char *filename = NULL;

    size_t option = 0;
    while (option != OPT_EXIT)
    {
        print_menu();
        if ((rc = get_option(&option)))
            print_error(rc);    // Выбор пользователем пункта меню с последующей обработкой ошибок
        else if ((rc = controller(option, &bin_tree, &avl_tree, &filename)))
            print_error(rc);
    }
    bin_tree_clear(&bin_tree);
    avl_tree_clear(&avl_tree);
    free(filename);

    return rc;
}

int controller(int option, bin_tree_t *bin_tree, avl_tree_t *avl_tree, char **filename)
{
    int rc = RC_OK;

    switch (option)
    {
        case OPT_PRINT_INFO:
            print_info();
            break;
        case OPT_READ:
            rc = read(bin_tree, avl_tree, filename);
            break;
        case OPT_PRINT:
            print(*bin_tree, *avl_tree);
            break;
        case OPT_FIND:
            rc = find(bin_tree, avl_tree, *filename);
            break;
        case OPT_CMP:
            // rc = compare(*filename, *bin_tree, *avl_tree);
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
