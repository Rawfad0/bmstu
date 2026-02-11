#include "ui.h"
#include "consts.h"
#include "model.h"
#include "compar.h"

#include <stdio.h>

int controller(int option);

int main(void)
{
    int rc = RC_OK;

    size_t option = 0;
    while (option != OPT_EXIT)
    {
        print_menu();
        if ((rc = get_option(&option)))
            print_error(rc);    // Выбор пользователем пункта меню с последующей обработкой ошибок
        else if ((rc = controller(option)))
            print_error(rc);
    }

    return rc;
}

int controller(int option)
{
    int rc = RC_OK;

    switch (option)
    {
        case OPT_PRINT_INFO:
        {
            print_info();
            break;
        }
        case OPT_MODEL_SAQ:
        {
            saq_model(1);
            break;
        }
        case OPT_MODEL_LLQ:
        {
            llq_model(1);
            break;
        }
        case OPT_COMPARE:
        {
            compare();
            break;
        }
        case OPT_EXIT:
        {
            printf("Завершение программы.\n");
            break;
        }
        default:
            printf("Некорректный номер пункта меню. Действия не существует.\n");
            return RC_INCORRECT_OPTION;
            break;
    }
    return rc;
}
