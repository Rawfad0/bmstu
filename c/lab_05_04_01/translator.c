#include "translator.h"

int binary_to_text(FILE *b, FILE *f)
{
    size_t size;
    struct student stud;
    int r;

    r = bin_file_size(b, &size);
    if (r == 0 && size % sizeof(struct student) == 0)
    {
        for (size_t i = 0; i < size / sizeof(struct student); i++)
        {
            fread(&stud, sizeof(struct student), 1, b);
            fprintf(f, "%s\n%s\n%d %d %d %d\n", stud.last_name, stud.first_name, 
            stud.grades[0], stud.grades[1], stud.grades[2], stud.grades[3]);
        }
    }
    else
        return EXIT_CODE_INCORRECT_SIZE;
    
    return 0;
}

int text_to_binary(FILE *b, FILE *f)
{
    struct student stud;

    while (!feof(f))
    {
        if (fscanf(f, "%s %s %u %u %u %u", stud.last_name, stud.first_name, 
        &stud.grades[0], &stud.grades[1], &stud.grades[2], &stud.grades[3]) != 6)
            return EXIT_CODE_INCORRECT_INPUT;
        fwrite(&stud, sizeof(struct student), 1, b);
    }
    return 0;
}