#include "io.h"

void print_student(struct student stud)
{
    printf("%s\n%s\n%d %d %d %d\n", stud.last_name, stud.first_name, 
    stud.grades[0], stud.grades[1], stud.grades[2], stud.grades[3]);
}

int print_students(FILE *f)
{
    size_t size;
    struct student stud;
    int r;

    r = bin_file_size(f, &size);
    if (r == 0 && size % sizeof(struct student) == 0)
    {
        for (size_t i = 0; i < size / sizeof(struct student); i++)
        {
            fread(&stud, sizeof(struct student), 1, f);
            print_student(stud);
        }
    }
    else
        return EXIT_CODE_INCORRECT_SIZE;
    
    return 0;
}
