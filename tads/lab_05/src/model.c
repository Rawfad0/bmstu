#include "model.h"

#define QUITED_COUNT_MAX 1000

#define RAND_AC 100000000

// Временные интервалы аппаратов
#define OA1_T1 0
#define OA1_T2 1.7

#define OA2_T1 0
#define OA2_T2 2

// Вероятность отправки в "хвост" очереди
#define P 0.1

double rand_0to1(void)
{
    // double res = (double) rand() / RAND_MAX;
    // printf("!!!!! res:%lf\n\n", res);
    return (double) rand() / RAND_MAX;
}

double get_rand_time(double t_min, double t_max)
{
    return (t_max - t_min) * ((double) rand_0to1()) + t_min;
}

typedef struct
{
    double clock1;      // Таймер 1й очереди
    double clock2;      // Таймер 1й очереди
    double sleep2;      // Время простоя ОА2
    double average_in_q;// Время пребывания заявок в очереди

    size_t oa1_c;       // Количество срабатываний ОА1
    size_t oa2out_c;    // Счетчик вышедших из ОА2
    size_t oa2out_c100; // Счетчик сотен вышедших из ОА2
    size_t ql1;         // Длина 1й очереди
    size_t ql2;         // Длина 2й очереди
    double average_l1;  // Средняя длина 1й очереди * время
    double average_l2;  // Средняя длина 2й очереди * время
} measures_t;

// void print_m(measures_t m)
// {
//     printf("%lf %lf\n%zu %zu\n%zu %zu\n\n", m.clock1, m.clock2, m.ql1, m.ql2, m.oa1_c, m.oa2out_c);
// }

void saq1_process(measures_t *m, sa_queue_t *saq1, sa_queue_t *saq2)
{
    double time = get_rand_time(OA1_T1, OA1_T2);
    applic_t a;
    saq_pop(saq1, &a);
    m->clock1 += time;
    m->average_in_q += m->clock1 - a.time;

    m->oa1_c++;
    m->average_l1 += m->ql1 * time;

    if (rand_0to1() > P)
    {
        saq_push(saq2, make_application(m->clock1));
        m->ql1--;
        m->ql2++;
    }
    else
        saq_push(saq1, make_application(m->clock1));
}

void saq2_process(measures_t *m, sa_queue_t *saq1, sa_queue_t *saq2)
{
    double time = get_rand_time(OA2_T1, OA2_T2);
    applic_t a;
    saq_pop(saq2, &a);
    if (a.time > m->clock2)
    {
        m->sleep2 += a.time - m->clock2;
        m->clock2 = a.time;
    }
    m->clock2 += time;
    m->average_in_q += m->clock2 - a.time;

    m->oa2out_c++;
    m->average_l2 += m->ql2 * time;

    saq_push(saq1, make_application(m->clock2));
    m->ql1++;
    m->ql2--;
}

void saq_model(int code)
{
    measures_t m = {0, 0, 0, 0,
                    0, 0, 0, 100, 0, 0, 0};
    sa_queue_t *saq1 = saq_init();
    for (size_t i = 0; i < 100; i++)
        saq_push(saq1, make_application(0));    // Заполнение 1й очереди
    sa_queue_t *saq2 = saq_init();
    // Шапка таблицы
    if (code)
    {
        printf("|%*s|%*s|%*s|\n", COL, "Q2_PASS", 2*COL+1, "CURRENT LENGHT", 2*COL+1, "AVERAGE LENGHT");
        printf("|%*s|%*s|%*s|%*s|%*s|\n", COL, "", COL, "QUEUE 1", COL, "QUEUE 2", 
                                                    COL, "QUEUE 1", COL, "QUEUE 2");
    
    }
    while (m.oa2out_c <= QUITED_COUNT_MAX)
    {
        // print_m(m);
        if (m.clock1 <= m.clock2)
            if (m.ql1 > 0)
                saq1_process(&m, saq1, saq2);
            else
                saq2_process(&m, saq1, saq2);
        else
            if (m.ql2 > 0)
                saq2_process(&m, saq1, saq2);
            else
                saq1_process(&m, saq1, saq2);
        if (code && m.oa2out_c % 100 == 0 && m.oa2out_c != m.oa2out_c100)
        {
            m.oa2out_c100 = m.oa2out_c;
            printf("|%*zu|%*zu|%*zu|%*lf|%*lf|\n", COL, m.oa2out_c100, COL, m.ql1, COL, m.ql2, 
                    COL, m.average_l1 / m.clock1, COL, m.average_l2 / m.clock2);
        }
    }
    if (code)
    {
        printf("\nМоделирование завершено.\t\tВремя:\t%*s%*s%*s\n", 
            COL2, "MODEL", COL2, "ESTIMATED", COL2, "DIFF%%");
        printf("Общее время моделирования:\t\t\t%*lf%*lf%*lf\n", 
            COL2, m.clock2, COL2, (double) 10000, COL2, 100 * (m.clock2 - 10000) / 10000);
        printf("Время простоя ОА2: \t\t\t\t%*lf%*lf%*lf\n", 
            COL2, m.sleep2, COL2, (double) 5500, COL2, 100 * (m.sleep2 - 5500) / 5500);
        printf("Количество срабатываний ОА1: \t\t\t%*zu%*lf%*lf\n", 
            COL2, m.oa1_c, COL2, (double) 3333, COL2, (double) 100 * ( (double) m.oa1_c - 3333) / 3333);
        printf("Среднее время пребывания заявок в очереди: \t%*lf%*lf%*lf\n", 
            COL2, m.average_in_q / (m.oa1_c + m.oa2out_c), COL2, 227.3, COL2, 100 * ((m.average_in_q / (m.oa1_c + m.oa2out_c)) - 227.3) / 227.3);
        // [(3333-100)*300 / (1+0.3) + 100*(300/2) / (1+0.3)]/3333 = 227.307
    }
    free(saq1);
    free(saq2);
}

void llq1_process(measures_t *m, ll_queue_t *llq1, ll_queue_t *llq2)
{
    double time = get_rand_time(OA1_T1, OA1_T2);
    applic_t a;
    llq_pop(llq1, &a);
    m->clock1 += time;
    m->average_in_q += m->clock1 - a.time;

    m->oa1_c++;
    m->average_l1 += m->ql1 * time;

    if (rand_0to1() > P)
    {
        llq_push(llq2, make_application(m->clock1));
        m->ql1--;
        m->ql2++;
    }
    else
        llq_push(llq1, make_application(m->clock1));
}

void llq2_process(measures_t *m, ll_queue_t *llq1, ll_queue_t *llq2)
{
    double time = get_rand_time(OA2_T1, OA2_T2);
    applic_t a;
    llq_pop(llq2, &a);
    if (a.time > m->clock2)
    {
        m->sleep2 += a.time - m->clock2;
        m->clock2 = a.time;
    }
    m->clock2 += time;
    m->average_in_q += m->clock2 - a.time;

    m->oa2out_c++;
    m->average_l2 += m->ql2 * time;

    llq_push(llq1, make_application(m->clock2));
    m->ql1++;
    m->ql2--;
}

void llq_model(int code)
{
    measures_t m = {0, 0, 0, 0,
                    0, 0, 0, 100, 0, 0, 0};
    ll_queue_t *llq1 = llq_init();
    for (size_t i = 0; i < 100; i++)
        llq_push(llq1, make_application(0));    // Заполнение 1й очереди
    ll_queue_t *llq2 = llq_init();
    // Шапка таблицы
    if (code)
    {
        printf("|%*s|%*s|%*s|\n", COL, "Q2_PASS", 2*COL+1, "CURRENT LENGHT", 2*COL+1, "AVERAGE LENGHT");
        printf("|%*s|%*s|%*s|%*s|%*s|\n", COL, "", COL, "QUEUE 1", COL, "QUEUE 2", 
                                                    COL, "QUEUE 1", COL, "QUEUE 2");
    
    }
    while (m.oa2out_c <= QUITED_COUNT_MAX)
    {
        // print_m(m);
        if (m.clock1 <= m.clock2)
            if (m.ql1 > 0)
                llq1_process(&m, llq1, llq2);
            else
                llq2_process(&m, llq1, llq2);
        else
            if (m.ql2 > 0)
                llq2_process(&m, llq1, llq2);
            else
                llq1_process(&m, llq1, llq2);
        if (code && m.oa2out_c % 100 == 0 && m.oa2out_c != m.oa2out_c100)
        {
            m.oa2out_c100 = m.oa2out_c;
            printf("|%*zu|%*zu|%*zu|%*lf|%*lf|\n", COL, m.oa2out_c100, COL, m.ql1, COL, m.ql2, 
                    COL, m.average_l1 / m.clock1, COL, m.average_l2 / m.clock2);
        }
    }
    if (code)
    {
        printf("\nМоделирование завершено.\t\tВремя:\t%*s%*s%*s\n", 
            COL2, "MODEL", COL2, "ESTIMATED", COL2, "DIFF%%");
        printf("Общее время моделирования:\t\t\t%*lf%*lf%*lf\n", 
            COL2, m.clock2, COL2, (double) 10000, COL2, 100 * (m.clock2 - 10000) / 10000);
        printf("Время простоя ОА2: \t\t\t\t%*lf%*lf%*lf\n", 
            COL2, m.sleep2, COL2, (double) 5500, COL2, 100 * (m.sleep2 - 5500) / 5500);
        printf("Количество срабатываний ОА1: \t\t\t%*zu%*lf%*lf\n", 
            COL2, m.oa1_c, COL2, (double) 3333, COL2, (double) 100 * ( (double) m.oa1_c - 3333) / 3333);
        printf("Среднее время пребывания заявок в очереди: \t%*lf%*lf%*lf\n", 
            COL2, m.average_in_q / (m.oa1_c + m.oa2out_c), COL2, 227.3, COL2, 100 * ((m.average_in_q / (m.oa1_c + m.oa2out_c)) - 227.3) / 227.3);
        // [(3333-100)*300 / (1+0.3) + 100*(300/2) / (1+0.3)]/3333 = 227.307
    }
    llq_free(llq1);
    llq_free(llq2);
    free(llq1);
    free(llq2);
}
