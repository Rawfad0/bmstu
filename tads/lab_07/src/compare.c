#include "compare.h"

#define COL1 25
#define COL2 10
#define COL3 10

//
// Функции замера времени
//
struct measure_times
{
    double tree_timer;
    double avl_timer;
    double hto_timer;
    double htc_timer;
    bin_tree_t tree;
    bin_tree_t avl;
    hto_t hto;
    htc_t htc;
    size_t c2restr;
};

void measure_search(const char *key, int *value, void *n)
{
    if (key == NULL && value == NULL)
        return;

    struct measure_times *times = n;
    struct timeval tb, te;

    int cmp_count = 0;
    // Замер поиска в дереве
    cmp_count = 0;
    gettimeofday(&tb, NULL);
    for (size_t i = 0; i < REPEAT; i++)
    bin_tree_find(times->tree, key, &cmp_count);
    gettimeofday(&te, NULL);
    times->tree_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
    // Замер поиска в сбалансированном дереве
    cmp_count = 0;
    gettimeofday(&tb, NULL);
    for (size_t i = 0; i < REPEAT; i++)
    bin_tree_find(times->avl, key, &cmp_count);
    gettimeofday(&te, NULL);
    times->avl_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
    // Замер поиска в hto
    cmp_count = 0;
    gettimeofday(&tb, NULL);
    for (size_t i = 0; i < REPEAT; i++)
        hto_find(times->hto, key, &cmp_count);
    gettimeofday(&te, NULL);
    times->hto_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
    // Замер поиска в htc
    cmp_count = 0;
    gettimeofday(&tb, NULL);
    for (size_t i = 0; i < REPEAT; i++)
        htc_find(times->htc, key, &cmp_count, times->c2restr);
    gettimeofday(&te, NULL);
    times->htc_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
}

int compare_time(bin_tree_t tree, bin_tree_t avl, hto_t hto, htc_t htc, size_t c2restr)
{
    struct measure_times times = {0, 0, 0, 0, tree, avl, hto, htc, c2restr};
    bin_tree_each(tree, (*measure_search), &times);
    printf("|%*s|%*lf|%*lf|%*lf|%*lf|\n", COL1, "Search time (100 rep)", 
        COL2, times.tree_timer, COL3, times.avl_timer, 
        COL2, times.hto_timer, COL3, times.htc_timer);
    return RC_OK;
}

//
// Функции замера количества сравнений
//
struct measure_cmps
{
    int tree_cmp;
    int avl_cmp;
    int hto_cmp;
    int htc_cmp;
    bin_tree_t tree;
    bin_tree_t avl;
    hto_t hto;
    htc_t htc;
    size_t c2restr;
};

void measure_cmps(const char *key, int *value, void *n)
{
    if (key == NULL && value == NULL)
        return;

    struct measure_cmps *cmps = n;
    // Замер поиска в дереве
    bin_tree_find(cmps->tree, key, &cmps->tree_cmp);
    // Замер поиска в сбалансированном дереве
    bin_tree_find(cmps->avl, key, &cmps->avl_cmp);
    // Замер поиска в hto
    hto_find(cmps->hto, key, &cmps->hto_cmp);
    // Замер поиска в htc
    htc_find(cmps->htc, key, &cmps->htc_cmp, cmps->c2restr);
}

void f_counter(const char *key, int *value, void *n)
{
    size_t *counter = n;
    if (key != NULL && value != NULL)
        (*counter)++;
}

int compare_cmps(bin_tree_t tree, bin_tree_t avl, hto_t hto, htc_t htc, size_t c2restr)
{
    size_t counter = 0;
    bin_tree_each(tree, (*f_counter), &counter);

    struct measure_cmps cmps = {0, 0, 0, 0, tree, avl, hto, htc, c2restr};
    bin_tree_each(tree, (*measure_cmps), &cmps);
    printf("|%*s|%*lf|%*lf|%*lf|%*lf|\n", COL1, "COMPARES", 
        COL2, (double) cmps.tree_cmp / counter, COL3, (double) cmps.avl_cmp / counter, 
        COL2, (double) cmps.hto_cmp / counter, COL3, (double) cmps.htc_cmp / counter);
    return RC_OK;
}

//
// Функции замера памяти
//
struct measure_mems
{
    int tree_mem;
    int avl_mem;
    int hto_mem;
    int htc_mem;
    bin_tree_t tree;
    bin_tree_t avl;
    hto_t hto;
    htc_t htc;
};

void measure_mems(const char *key, int *value, void *n)
{
    if (key == NULL && value == NULL)
        return;

    struct measure_mems *mems = n;
    // Замер поиска в дереве
    mems->tree_mem += sizeof(char) * (strlen(key) + 1) + sizeof(char *) + 2 * sizeof(bin_tree_t);
    // Замер поиска в сбалансированном дереве
    mems->avl_mem += sizeof(char) * (strlen(key) + 1) + sizeof(char *) + sizeof(int) + 2 * sizeof(bin_tree_t);
    // Замер поиска в hto
    mems->hto_mem += sizeof(char) * (strlen(key) + 1) + sizeof(char *) + sizeof(void *);
    // Замер поиска в htc
    mems->htc_mem += sizeof(char) * (strlen(key) + 1);
}

int compare_mem(bin_tree_t tree, bin_tree_t avl, hto_t hto, htc_t htc)
{
    struct measure_mems mems = {0, 0, get_hto_table_size(hto)*sizeof(void *), get_htc_table_size(htc)*sizeof(char *), tree, avl, hto, htc};
    bin_tree_each(tree, (*measure_mems), &mems);
    printf("|%*s|%*d|%*d|%*d|%*d|\n", COL1, "MEMORY", 
        COL2, mems.tree_mem, COL3, mems.avl_mem, 
        COL2, mems.hto_mem, COL3, mems.htc_mem);
    return RC_OK;
}

int compare(char *filename, size_t c2restr)
{
    int rc = RC_OK;
    if (filename == NULL)
        return RC_INCORRECT_FILE;

    bin_tree_t tree = NULL;
    bin_tree_t avl = NULL;
    hto_t hto = hto_create();
    htc_t htc = htc_create();
    if ((rc = read_file(&tree, &hto, &htc, filename, c2restr)) != RC_OK)
        return rc;
    if ((rc = read_file(&avl, &hto, &htc, filename, c2restr)) != RC_OK)
        return rc;
    balance(&avl);

    printf("+%.*s+%.*s+%.*s+%.*s+%.*s+\n", COL1, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150);
    printf("|%*s|%-*s|%-*s|%-*s|%-*s|\n", COL1, "", COL2, "TREE", COL3, "AVL", COL2, "HT_OPEN", COL3, "HT_CLOSED");
    printf("+%.*s+%.*s+%.*s+%.*s+%.*s+\n", COL1, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150);
    
    if ((rc = compare_cmps(tree, avl, hto, htc, c2restr)) != RC_OK);
    else if ((rc = compare_time(tree, avl, hto, htc, c2restr)) != RC_OK);
    else if ((rc = compare_mem(tree, avl, hto, htc)) != RC_OK);
    else
        rc = RC_OK;
    printf("+%.*s+%.*s+%.*s+%.*s+%.*s+\n", COL1, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150);
    
    bin_tree_clear(&tree);
    bin_tree_clear(&avl);
    hto_destroy(&hto);
    htc_destroy(&htc);
    return rc;
}

int compare_restr(char *filename, hto_t *hto_table, htc_t *htc_table, size_t c2restr)
{
    if (filename == NULL)
        return RC_INCORRECT_FILE;
    int rc = RC_OK;
    double hto_timer = 0, htc_timer = 0;
    struct timeval tb, te;

    printf("Заполненность 1й таблицы: %zu/%zu = %lf%%\n", 
        hto_count(*hto_table), c2restr*get_hto_table_size(*hto_table),
        (double) 100*hto_count(*hto_table) / (c2restr*get_hto_table_size(*hto_table)));
    printf("Заполненность 2й таблицы: %zu/%zu = %lf%%\n", 
        htc_count(*htc_table), get_htc_table_size(*htc_table),
        (double) 100*htc_count(*htc_table) / get_htc_table_size(*htc_table));

    // Замер вставки в hto
    gettimeofday(&tb, NULL);
    hto_restruct(hto_table, c2restr);
    gettimeofday(&te, NULL);
    hto_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;

    // Замер вставки в htc
    gettimeofday(&tb, NULL);
    htc_restruct(htc_table, c2restr);
    gettimeofday(&te, NULL);
    htc_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;

    printf("Реструктуризация хеш-таблицы с открытым хешированием (в секундах): %lf\n", hto_timer);
    printf("Реструктуризация хеш-таблицы с закрытым хешированием (в секундах): %lf\n", htc_timer);
    
    printf("Заполненность 1й таблицы: %zu/%zu = %lf%%\n", 
        hto_count(*hto_table), c2restr*get_hto_table_size(*hto_table),
        (double) 100*hto_count(*hto_table) / (c2restr*get_hto_table_size(*hto_table)));
    printf("Заполненность 2й таблицы: %zu/%zu = %lf%%\n", 
        htc_count(*htc_table), get_htc_table_size(*htc_table),
        (double) 100*htc_count(*htc_table) / get_htc_table_size(*htc_table));
    return rc;
}