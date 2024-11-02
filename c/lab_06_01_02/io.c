#include "io.h"

int read_objects(char *file_name, struct object *obj_arr, size_t *n)
{
    FILE *f;
    struct object temp;
    int rc = 0;

    f = fopen(file_name, "r");
    if (f)
    {
        while (!feof(f) && rc == 0)
        {
            fgets(temp.name, sizeof(temp.name), f);
            if (fscanf(f, "%lf\n%lf\n", &temp.mass, &temp.volume) != 2)
                rc = EXIT_CODE_INCORRECT_INPUT;             // Считанные данные не являются структурой
            else if (*n >= N_MAX)
                rc = EXIT_CODE_INCORRECT_NUMBER_OF_OBJECTS; // Количество предметов превысило допустимое значение
            else if (strlen(temp.name) > NAME_MAX || temp.mass < MACHINE_EPS || temp.volume < MACHINE_EPS)
                rc = EXIT_CODE_INCORRECT_OBJECT;            // Имя предмета длинее 25 символов или неположительная масса или объем
            else
            {
                if (temp.name[strlen(temp.name) - 1] == '\n') 
                    temp.name[strlen(temp.name) - 1] = '\0';
                obj_arr[*n] = temp;
                ++*n;
            } 
        }
        fclose(f);
    }
    else
        rc = EXIT_CODE_INCORRECT_FILE;                      // Не удалось открыть файл
    
    return rc;
}

void print_all_objects(struct object *obj_arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%s\n%lf\n%lf\n", obj_arr[i].name, obj_arr[i].mass, obj_arr[i].volume);
}
