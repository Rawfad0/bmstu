#include "ui.h"
#include "consts.h"
#include "bin_tree.h"
#include "hash_open.h"
#include "hash_closed.h"
#include "funcs.h"
#include "compare.h"

#include <stdio.h>

int controller(int option, bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char **filename, size_t *c2restr);

int main(void)
{
    int rc = RC_OK;

    bin_tree_t tree = NULL;
    hto_t hto_table = hto_create();
    htc_t htc_table = htc_create();
    size_t c2restr = 3;
    char *filename = NULL;

    size_t option = 0;
    while (option != OPT_EXIT)
    {
        print_menu();
        if ((rc = get_option(&option)))
            print_error(rc);    // Выбор пользователем пункта меню с последующей обработкой ошибок
        else if ((rc = controller(option, &tree, &hto_table, &htc_table, &filename, &c2restr)))
            print_error(rc);
    }
    bin_tree_clear(&tree);
    hto_destroy(&hto_table);
    htc_destroy(&htc_table);
    free(filename);

    return rc;
}

int controller(int option, bin_tree_t *tree, hto_t *hto_table, htc_t *htc_table, char **filename, size_t *c2restr)
{
    int rc = RC_OK;
    switch (option)
    {
        case OPT_PRINT_INFO:
            print_info();
            break;
        case OPT_READ:
            rc = read(tree, hto_table, htc_table, filename, *c2restr);
            break;
        case OPT_PRINT:
            print(*hto_table, *htc_table);
            break;
        case OPT_FIND:
            rc = find(*filename, tree, hto_table, htc_table, *c2restr);
            break;
        case OPT_REM:
            rc = remove_word(*filename, tree, *hto_table, *htc_table, *c2restr);
            break;
        case OPT_BALANCE:
            rc = balance(tree);
            break;
        case OPT_CMP:
            rc = compare(*filename, *c2restr);
            break;
        case OPT_CMP_HASH:
            rc = compare_restr(*filename, hto_table, htc_table, *c2restr);
            break;
        case OPT_WRITE:
            rc = write(*tree);
            break;
        case OPT_c2restr:
            rc = change_c2restr(c2restr, tree, hto_table, htc_table, *filename);
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
