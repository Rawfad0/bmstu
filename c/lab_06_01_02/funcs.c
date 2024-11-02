#include "funcs.h"

/**
 * @brief Вычисляет плотность предмета
 * 
 * @param obj предмет
 * @return double плотность
 */
double calc_obj_density(struct object obj)
{
    return obj.mass / obj.volume;
}

/**
 * @brief Перестановка двух элементов массива предметов
 * 
 * @param obj1 первый предмет 
 * @param obj2 второй предмет
 */
void swap_objects(struct object *obj1, struct object *obj2)
{
    struct object temp = *obj1;
    *obj1 = *obj2;
    *obj2 = temp;
}

void sort_objects_by_density(struct object *obj_arr, size_t n)
{
    size_t min_i;

    // Сортировка выбором
    for (size_t i = 0; i < n; i++)
    {
        min_i = i;
        for (size_t j = i + 1; j < n; j++)
            if (calc_obj_density(obj_arr[j]) - calc_obj_density(obj_arr[min_i]) < -MACHINE_EPS)
                min_i = j;

        if (min_i != i)
            swap_objects(&obj_arr[min_i], &obj_arr[i]);
    }
}

int find_prefix(struct object *obj_arr, size_t n, struct object *found_obj_arr, size_t *found_n, char *prefix)
{
    size_t len = strlen(prefix);
    *found_n = 0;
    int rc = 0;

    for (size_t i = 0; i < n; i++)
        if (!strncmp(obj_arr[i].name, prefix, len))
            found_obj_arr[(*found_n)++] = obj_arr[i];

    if (!*found_n)
        rc = EXIT_CODE_NO_OBJ_FOUND;
    
    return rc;
}
