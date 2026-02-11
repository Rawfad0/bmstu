#include "compare.h"

#define COL1 25
#define COL2 10
#define COL3 10

int file_find(char *filename, char *str)
{
    int rc = RC_OK;
    if (filename == NULL)
        return RC_INCORRECT_FILE;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return RC_INCORRECT_FILE;
    char *tmp = NULL;
    while (!feof(f) && rc == RC_OK)
    {
        if (get_input(&tmp, f) != RC_OK)
            break;
        if (strcmp(str, tmp) == 0)
        {
            free(tmp);
            break;
        }
        free(tmp);
    }
    fclose(f);
    return rc;
}

struct measure_times
{
    double tree_timer;
    double file_timer;
    char *filename;
    bin_tree_t tree;
};

void measure_search(const char *key, int *value, void *n)
{
    if (key == NULL && value == NULL)
        return;

    struct measure_times *times = n;
    struct timeval tb, te;

    int *num = NULL;
    int cmp_count = 0;

    // Замер поиска в файле
    gettimeofday(&tb, NULL);
    file_find(times->filename, (char *) key);
    gettimeofday(&te, NULL);
    times->file_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;
    
    // Замер поиска в дереве
    gettimeofday(&tb, NULL);
    bin_tree_find(times->tree, key, &num, &cmp_count);
    gettimeofday(&te, NULL);
    times->tree_timer += te.tv_sec - tb.tv_sec + (te.tv_usec - tb.tv_usec) / 1000000.0;

}

int compare_time(char *filename, bin_tree_t tree)
{
    if (filename == NULL)
        return RC_INCORRECT_FILE;

    struct measure_times times = {0, 0, filename, tree};
    bin_tree_each(tree, (*measure_search), &times);
    printf("|%*s|%*lf|%*lf|\n", COL1, "Search time (1 rep)", COL2, times.file_timer, COL3, times.tree_timer);
    return RC_OK;
}

int compare_cmps(char *filename, bin_tree_t tree)
{
    int cmp_count_file = 0, cmp_count_tree = 0;
    size_t counter = 0;

    int rc = RC_OK;
    bt_rc_t rc_bt = BIN_TREE_OK;
    if (filename == NULL)
        return RC_INCORRECT_FILE;
    
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return RC_INCORRECT_FILE;
    int res;
    int *num;
    char *tmp = NULL;
    while (!feof(f) && rc == RC_OK && rc_bt == BIN_TREE_OK)
    {
        if (get_input(&tmp, f) != RC_OK)
            break;
        // Замер поиска в файле
        res = 0;
        num = NULL;
        rc = find_in_file(filename, tmp, &res, &cmp_count_file);
        // Замер поиска в дереве
        res = 0;
        num = NULL;
        rc_bt = bin_tree_find(tree, tmp, &num, &cmp_count_tree);
        
        counter++;
        free(tmp);
    }
    fclose(f);
    if (rc == RC_OK)
        printf("|%*s|%*lf|%*lf|\n", COL1, "Compares", 
               COL2, (double)cmp_count_file / counter, COL3, (double)cmp_count_tree / counter);
    return rc;
}

void count_mem(const char *key, int *value, void *n)
{
    int *mem_counter = n;
    if (key != NULL && value != NULL)
        *mem_counter += sizeof(char) * (strlen(key) + 1) + sizeof(char *) + sizeof(int) + 2 * sizeof(bin_tree_t);
}

int compare_mem(char *filename, bin_tree_t tree)
{
    size_t file_mem = 0, tree_mem = 0;

    int rc = RC_OK;
    if (filename == NULL)
        return RC_INCORRECT_FILE;
    // Замер дерева
    bin_tree_each(tree, (*count_mem), &tree_mem);
    // Замер файла
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return RC_INCORRECT_FILE;
    char *tmp = NULL;
    while (!feof(f) && rc == RC_OK)
    {
        if (get_input(&tmp, f) != RC_OK)
            break;
        file_mem += sizeof(char) * (strlen(tmp) + 1);
        free(tmp);
    }
    fclose(f);
    if (rc == RC_OK)
        printf("|%*s|%*zu|%*zu|\n", COL1, "Memory (bytes)", COL2, file_mem, COL3, tree_mem);
    return rc;
}


int compare(char *filename, bin_tree_t tree)
{
    int rc = RC_OK;
    if (filename == NULL || tree == NULL)
        return RC_INCORRECT_FILE;
    printf("+%.*s+%.*s+%.*s+\n", COL1, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150);
    printf("|%*s|%-*s|%-*s| \n", COL1, "", COL2, "FILE", COL3, "TREE");
    printf("+%.*s+%.*s+%.*s+\n", COL1, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150);
    
    if ((rc = compare_cmps(filename, tree)) != RC_OK);
    else if ((rc = compare_time(filename, tree)) != RC_OK);
    else if ((rc = compare_mem(filename, tree)) != RC_OK);
    else
        rc = RC_OK;
    printf("+%.*s+%.*s+%.*s+\n", COL1, BLANKSx150, COL2, BLANKSx150, COL3, BLANKSx150);

    return rc;
}
