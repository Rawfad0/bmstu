#include "matrix.h"

#define RC_OK 0
#define RC_INCORRECT_INPUT 1

#define MAX_N 300
#define STEP 10
#define REPS 100


double measure(matrix_error_t (*func)(const matrix_t *, const matrix_t *, matrix_t **), const matrix_t *a, const matrix_t *b)
{
    clock_t tb, te;
    matrix_t *r = NULL;

    tb = clock();
    (*func)(a, b, &r);
    te = clock();

    matrix_free(&r);
    return 1000.0 * (te - tb) / CLOCKS_PER_SEC;
}

double measure_unsafe(void (*func)(const matrix_t *, const matrix_t *, matrix_t **), const matrix_t *a, const matrix_t *b)
{
    clock_t tb, te;
    matrix_t *r = NULL;

    tb = clock();
    (*func)(a, b, &r);
    te = clock();

    matrix_free(&r);
    return 1000.0 * (te - tb) / CLOCKS_PER_SEC;
}

int print_measurements(void)
{
    int rc = RC_OK;
    matrix_t *a = NULL, *b = NULL;
    double t_std, t_win, t_opt;
    srand(time(NULL));
    
    for (size_t i = STEP; i <= MAX_N; i += STEP)
    {
        a = matrix_create(i, i);
        b = matrix_create(i, i);
        t_std = 0, t_win = 0, t_opt = 0;
        for (size_t j = 0; j < REPS; j++)
        {
            matrix_rand_fill(a, -1000000.0, 1000000.0);
            matrix_rand_fill(b, -1000000.0, 1000000.0);

            // t_std += measure_unsafe(matrix_mult_standart_unsafe, a, b);
            // t_win += measure_unsafe(matrix_mult_winograd_unsafe, a, b);
            // t_opt += measure_unsafe(matrix_mult_winograd_opt_unsafe, a, b);
            t_std += measure(matrix_mult_standart, a, b);
            t_win += measure(matrix_mult_winograd, a, b);
            t_opt += measure(matrix_mult_winograd_opt, a, b);
        }
        printf("%zu %lf %lf %lf\n", i, t_std / REPS, t_win / REPS, t_opt / REPS);
        matrix_free(&a);
        matrix_free(&b);
    }
    return rc;
}

int main(void)
{
    int rc = print_measurements();
    if (rc == RC_INCORRECT_INPUT)
        printf("ERROR: INCORRECT INPUT\n");
    
    return rc;


    // srand(time(NULL));
    // matrix_t *a = NULL, *b = NULL, *r = NULL;

    // a = matrix_create(3, 3);
    // b = matrix_create(3, 3);
    // matrix_rand_fill(a, 0.0, 10.0);
    // matrix_rand_fill(b, 0.0, 10.0);
    // matrix_print(a);
    // matrix_print(b);
    // printf("STANDART\n");
    // matrix_mult_standart(a, b, &r);
    // matrix_print(r);

    // // matrix_free(&a);
    // // matrix_free(&b);
    // matrix_free(&r);


    // // a = matrix_create(3, 3);
    // // b = matrix_create(3, 3);
    // // matrix_rand_fill(a, 0.0, 10.0);
    // // matrix_rand_fill(b, 0.0, 10.0);
    // // matrix_print(a);
    // // matrix_print(b);
    // printf("Winograd\n");
    // matrix_mult_winograd(a, b, &r);
    // matrix_print(r);

    // // matrix_free(&a);
    // // matrix_free(&b);
    // matrix_free(&r);


    // // a = matrix_create(3, 3);
    // // b = matrix_create(3, 3);
    // // matrix_rand_fill(a, 0.0, 10.0);
    // // matrix_rand_fill(b, 0.0, 10.0);
    // // matrix_print(a);
    // // matrix_print(b);
    // printf("Winograd OPT\n");
    // matrix_mult_winograd_opt(a, b, &r);
    // matrix_print(r);

    // matrix_free(&a);
    // matrix_free(&b);
    // matrix_free(&r);

    // return 0;
}
