#include "compare.h"


long int measure_sas_add(sa_stack_t *stack, char *str)
{
    clock_t start, finish;

    start = clock();
    for (size_t i = 0; str[i] != '\n'; i++)
        sa_push(stack, str[i]);
    finish = clock();

    return finish - start;
}

long int measure_sas_del(sa_stack_t *stack, size_t num)
{
    clock_t start, finish;
    char ch = '\0';

    start = clock();
    for (size_t i = 0; i < num; i++)
        sa_pop(stack, &ch);
    finish = clock();

    return finish - start;
}

long int measure_sas_pal(sa_stack_t *stack, size_t len)
{
    clock_t start, finish;

    start = clock();
    sa_is_palindrome(stack, len);
    finish = clock();

    return finish - start;
}

long int measure_lls_add(ll_stack_t *stack, char *str)
{
    clock_t start, finish;

    start = clock();
    for (size_t i = 0; str[i] != '\n'; i++)
        ll_push(stack, str + i);
    finish = clock();

    return finish - start;
}

long int measure_lls_del(ll_stack_t *stack, size_t num)
{
    clock_t start, finish;
    list_t *tmp = NULL;

    start = clock();
    for (size_t i = 0; i < num; i++)
        ll_pop(stack, &tmp), free(tmp);;
    finish = clock();

    return finish - start;
}

long int measure_lls_pal(ll_stack_t *stack, size_t len)
{
    clock_t start, finish;

    start = clock();
    ll_is_palindrome(stack, len);
    finish = clock();
    
    return finish - start;
}

int measure_data_n(char *filename, size_t n)
{
    clock_t time_sas_a = 0, time_sas_d = 0, time_sas_p = 0, 
        time_lls_a = 0, time_lls_d = 0, time_lls_p = 0;
    // Инициализация стеков
    sa_stack_t sa_stack = { { '\0' }, NULL, NULL };
    sa_stack.pe = sa_stack.array + MAX_ARR_LEN;
    sa_stack.sp = sa_stack.array;
    ll_stack_t ll_stack = { NULL };
    // Чтение строки из файла
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return RC_INCORRECT_FILE;
    char *str = NULL;
    get_input(&str, f);

    for (size_t i = 0; i < N_REP; i++)
    {
        time_sas_a += measure_sas_add(&sa_stack, str);
        time_sas_d += measure_sas_del(&sa_stack, n);
        measure_sas_add(&sa_stack, str);
        time_sas_p += measure_sas_pal(&sa_stack, n);

        time_lls_a += measure_lls_add(&ll_stack, str);
        time_lls_d += measure_lls_del(&ll_stack, n);
        measure_lls_add(&ll_stack, str);
        time_lls_p += measure_lls_pal(&ll_stack, n);
    }
    fclose(f);
    free(str);
    ll_free(&ll_stack);
    // Вывод строчки измерений
    printf("%-*ld|%*ld|%*ld|%*ld|%*ld|%*ld|%*ld\n", 28, n, 
        18, time_sas_a, 18, time_sas_d, 18, time_sas_p, 
        18, time_lls_a, 18, time_lls_d, 18, time_lls_p);
    return RC_OK;
}

int compare(void)
{
    int rc = RC_OK;

    // Table header
    printf("%.*s\n", 142, BLANKSx150);
    printf("%*s%-*u|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s \n", 20, "Compare, ticks, N=", 8, N_REP, 
        18, "Static Stack Add", 18, "Static Stack Del", 18, "Static Palindrome",
        18, "List Stack Add", 18, "List Stack Del", 18, "List Palindrome");
    printf("%.*s\n", 142, BLANKSx150);
    
    // Данные для замеров
    size_t len_arr[] = { 10, 100, 1000, 10000 };
    char *filename_arr[] = { "./data/10.txt", "./data/100.txt", "./data/1000.txt", "./data/10000.txt" };
    // Основная таблица замеров
    for (size_t i  = 0; i < 4; i++)
        if ((rc = measure_data_n(filename_arr[i], len_arr[i])))
            return rc;

    printf("%.*s\n", 142, BLANKSx150);

    return rc;
}