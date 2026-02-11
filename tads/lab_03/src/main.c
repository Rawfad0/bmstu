#include "io.h"
#include "matrix.h"
#include "consts.h"
#include <stdio.h>

/**
 * @brief Контроллер аргументов программы
 * 
 * @param argc количество аргументов
 * @param argv аргументы
 * @param matrix1 первая матрица
 * @param matrix2 вторая матрица
 */
void arg_controller(int argc, char **argv, matrix_t *matrix1, matrix_t *matrix2,
                sparse_matrix_t *sparse_matrix1, sparse_matrix_t *sparse_matrix2);

/**
 * @brief Контроллер
 * 
 * @param option выбранный пользователем пункт меню
 * @param filename имя файла
 * @param table таблица
 * @param key_table таблица ключей
 * @return int код возврата
 */
int controller(int option, matrix_t *matrix1, matrix_t *matrix2, 
                sparse_matrix_t *sparse_matrix1, sparse_matrix_t *sparse_matrix2);

int main(int argc, char **argv)
{
    int rc = RC_OK;

    matrix_t matrix1 = { NULL, 0, 0 };
    matrix_t matrix2 = { NULL, 0, 0 };
    sparse_matrix_t sparse_matrix1 = { NULL, NULL, NULL, 0, 0, 0 };
    sparse_matrix_t sparse_matrix2 = { NULL, NULL, NULL, 0, 0, 0 };

    arg_controller(argc, argv, &matrix1, &matrix2, &sparse_matrix1, &sparse_matrix2);
    
    // printf("%p %p %p \n", (void *) sparse_matrix1.a, (void *) sparse_matrix1.ia, (void *) sparse_matrix1.ja);

    size_t option = 0;
    while (option != OPT_EXIT)
    {
        print_menu();
        if ((rc = get_option(&option)))
            print_error(rc);    // Выбор пользователем пункта меню с последующей обработкой ошибок
        else if ((rc = controller(option, &matrix1, &matrix2, &sparse_matrix1, &sparse_matrix2)))
            print_error(rc);
    }
    return rc;
}

void arg_controller(int argc, char **argv, matrix_t *matrix1, matrix_t *matrix2,
                sparse_matrix_t *sparse_matrix1, sparse_matrix_t *sparse_matrix2)
{
    if (argc == ARGC_0_INPUT)
        printf("На вход не поступило ни одного файла.\nОбе матрицы необходимо ввести в ручном режиме.\n");
    else if (argc == ARGC_1_INPUT)
    {
        printf("На вход поступил только один файл.\n");
        printf("Первая матрица будет прочитана из файла.\n");
        printf("Вторую матрицу необходимо ввести в ручном режиме.\n");
        if ((print_error(read_matrix(argv[1], matrix1))))
            printf("Ошибка: Не удалось прочитать первую матрицу.\n");
        else
        {
            printf("Матрица успешно прочитана.\n");
            *sparse_matrix1 = matrix_std_to_sparse(*matrix1);
        }
    }
    else if (argc == ARGC_2_INPUT)
    {
        printf("На вход поступили два файла.\nОбе матрицы будут прочитаны из файла.\n");
        if ((print_error(read_matrix(argv[1], matrix1))))
            printf("Ошибка: Не удалось прочитать первую матрицу.\n");
        else if ((print_error(read_matrix(argv[2], matrix2))))
        {
            printf("Ошибка: Не удалось прочитать вторую матрицу.\n");
            *sparse_matrix1 = matrix_std_to_sparse(*matrix1);
        }
        else
        {
            printf("Матрицы успешно прочитаны.\n");
            *sparse_matrix1 = matrix_std_to_sparse(*matrix1);
            *sparse_matrix2 = matrix_std_to_sparse(*matrix2);
        }
    }
    else
        print_error_msg(RC_INCORRECT_ARG_COUNT);
}

int controller(int option, matrix_t *matrix1, matrix_t *matrix2, 
                sparse_matrix_t *sparse_matrix1, sparse_matrix_t *sparse_matrix2)
{
    int rc = RC_OK;

    switch (option)
    {
        case OPT_PRINT_INFO:
            print_info();
            break;
        case OPT_INPUT_MATRIX_1:
            free_matrix(matrix1);
            if ((rc = input_matrix(matrix1)))
                free_matrix(matrix1);
            else
            {
                printf("Матрица успешно введена.\n");
                free_sparse_matrix(sparse_matrix1);
                *sparse_matrix1 = matrix_std_to_sparse(*matrix1);
            }
            break;

        case OPT_INPUT_MATRIX_2:
            free_matrix(matrix2);
            if ((rc = input_matrix(matrix2)))
                free_matrix(matrix2);
            else
            {
                printf("Матрица успешно введена.\n");
                free_sparse_matrix(sparse_matrix2);
                *sparse_matrix2 = matrix_std_to_sparse(*matrix2);
            }
            break;
        
        case OPT_PRINT_MATRIX_1:
            if (!(is_matrix_valid(*matrix1)))
                rc = RC_INVALID_MATRIX;
            else
                print_matrix(*matrix1), print_sparse_matrix(*sparse_matrix1);
            break;
        case OPT_PRINT_MATRIX_2:
            if (!(is_matrix_valid(*matrix2)))
                rc = RC_INVALID_MATRIX;
            else
                print_matrix(*matrix2), print_sparse_matrix(*sparse_matrix2);
            break;

        case OPT_PRINT_SUM_STD:
        {
            matrix_t matrix_res = { NULL, 0, 0 };
            matrix_res.matrix = allocate_matrix(matrix1->n, matrix1->m);
            if (!(is_matrix_valid(*matrix1) && is_matrix_valid(*matrix2) && is_matrix_valid(matrix_res)))
                rc = RC_INVALID_MATRIX;
            else if ((rc = matrix_addition(*matrix1, *matrix2, &matrix_res)));
            else
                print_matrix(matrix_res);
            free_matrix(&matrix_res); 
            break;
        }
        case OPT_PRINT_SUM_SPR:
        {
            sparse_matrix_t matrix_res = create_sparse_matrix(matrix1->n, matrix1->m);
            if (!(is_sparse_matrix_valid(*sparse_matrix1) && is_sparse_matrix_valid(*sparse_matrix2)))
                rc = RC_INVALID_MATRIX;
            else if ((rc = sparse_matrix_addition(*sparse_matrix1, *sparse_matrix2, &matrix_res)));
            else
            {
                matrix_t matrix = matrix_sparse_to_std(matrix_res);
                print_matrix(matrix);
            }
            free_sparse_matrix(&matrix_res); 
            break;
        }
        case OPT_COMPARISON:
            if (!(is_matrix_valid(*matrix1) && is_matrix_valid(*matrix2)
                && is_sparse_matrix_valid(*sparse_matrix1) && is_sparse_matrix_valid(*sparse_matrix2)))
                rc = RC_INVALID_MATRIX;
            else if (matrix1->n != matrix2->n || matrix1->m != matrix2->m)
                rc = RC_INCORRECT_SIZE;
            else if (sparse_matrix1->n != sparse_matrix2->n || sparse_matrix1->m != sparse_matrix2->m)
                rc = RC_INCORRECT_SIZE;
            else
                rc = compare(*matrix1, *matrix2, *sparse_matrix1, *sparse_matrix2);
            break;
        case OPT_EXIT:
            printf("Завершение программы.\n");
            free_matrix(matrix1), free_matrix(matrix2);
            free_sparse_matrix(sparse_matrix1), free_sparse_matrix(sparse_matrix2);
            break;
        default:
            printf("Некорректный номер пункта меню. Действия не существует.\n");
            return RC_INCORRECT_OPTION;
            break;
    }
    return rc;
}
