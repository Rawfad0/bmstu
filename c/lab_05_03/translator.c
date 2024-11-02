#include "translator.h"

/**
 * @brief Перевод бинарного файла целых чисел в текстовый файл целых чисел
 * 
 * @param b файловая переменная бинарного файл
 * @param f файловая переменная текстового файл
 * @return int код выхода
 */
int binary_to_text(FILE *b, FILE *f)
{
    size_t size;
    int num;
    int r;

    r = bin_file_size(b, &size);
    if (r == 0 && size % sizeof(int) == 0)
    {
        for (size_t i = 0; i < size / sizeof(int); i++)
        {
            fread(&num, sizeof(int), 1, b);
            fprintf(f, "%d\n", num);
        }
    }
    else
        return EXIT_CODE_INCORRECT_SIZE;
    
    return 0;
}

/**
 * @brief Перевод текстового файла целых чисел в бинарный файл целых чисел
 * 
 * @param b файловая переменная бинарного файл
 * @param f файловая переменная текстового файл
 * @return int код выхода
 */
int text_to_binary(FILE *b, FILE *f)
{
    int num;

    while (!feof(f))
    {
        if (fscanf(f, "%d", &num) != 1)
            return EXIT_CODE_INCORRECT_INPUT;
        fwrite(&num, sizeof(int), 1, b);
    }
    return 0;
}