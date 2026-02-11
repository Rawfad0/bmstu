#include "compar.h"


long int measure_saq_add(sa_queue_t *queue, size_t n)
{
    clock_t start, finish;

    start = clock();
    for (size_t i = 0; i < n; i++)
        saq_push(queue, make_application(0));
    finish = clock();

    return finish - start;
}

long int measure_saq_del(sa_queue_t *queue, size_t n)
{
    clock_t start, finish;
    applic_t a;

    start = clock();
    for (size_t i = 0; i < n; i++)
        saq_pop(queue, &a);
    finish = clock();

    return finish - start;
}

long int measure_saq_mod(void)
{
    clock_t start, finish;

    start = clock();
    saq_model(0);
    finish = clock();

    return finish - start;
}

long int measure_llq_add(ll_queue_t *queue, size_t n)
{
    clock_t start, finish;

    start = clock();
    for (size_t i = 0; i < n; i++)
        llq_push(queue, make_application(0));
    finish = clock();

    return finish - start;
}

long int measure_llq_del(ll_queue_t *queue, size_t n)
{
    clock_t start, finish;
    applic_t a;

    start = clock();
    for (size_t i = 0; i < n; i++)
        llq_pop(queue, &a);
    finish = clock();

    return finish - start;
}

long int measure_llq_mod(void)
{
    clock_t start, finish;

    start = clock();
    llq_model(0);
    finish = clock();
    
    return finish - start;
}

int measure_data_n(size_t n)
{
    clock_t time_saq_a = 0, time_saq_d = 0, 
        time_llq_a = 0, time_llq_d = 0;
    // time_saq_p = 0, time_llq_p = 0
    // // Инициализация
    sa_queue_t *saq = saq_init();
    ll_queue_t *llq = llq_init();

    for (size_t i = 0; i < N_REP; i++)
    {
        time_saq_a += measure_saq_add(saq, n);
        time_saq_d += measure_saq_del(saq, n);
        
        time_llq_a += measure_llq_add(llq, n);
        time_llq_d += measure_llq_del(llq, n);
    }
    llq_free(llq);
    free(llq);
    free(saq);
    // Вывод строчки измерений
    printf("%*ld|%*ld|%*ld|%*ld|%*ld\n", 28, n, 
        18, time_saq_a, 18, time_saq_d, 
        18, time_llq_a, 18, time_llq_d);
    return RC_OK;
}

int compare(void)
{
    int rc = RC_OK;

    // Table header
    printf("%.*s\n", 120, BLANKSx150);
    printf("%*s%-*u|%-*s|%-*s|%-*s|%-*s \n", 20, "Compare, ticks, N=", 8, N_REP, 
        18, "Static Queue Add", 18, "Static Queue Del", 18, "List Queue Add", 18, "List Queue Del");
    printf("%.*s\n", 120, BLANKSx150);
    
    // Данные для замеров
    size_t len_arr[] = { 1, 10, 50, 100 };
    // Основная таблица замеров
    for (size_t i  = 0; i < 4; i++)
        if ((rc = measure_data_n(len_arr[i])))
            return rc;
    printf("%.*s\n", 120, BLANKSx150);

    printf("Model:\n");
    clock_t time_saq_p = measure_saq_mod(), time_llq_p = measure_llq_mod();
    printf("Static %ld\n", time_saq_p);    
    printf("List   %ld\n", time_llq_p);

    printf("%zu\n", sizeof(applic_t));
    return rc;
}
