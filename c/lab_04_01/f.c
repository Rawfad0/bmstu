#include "f.h"

/**
 * @brief Поиск первого вхождения в str1 символа из str2
 * 
 * @param str1 строка для поиска
 * @param str2 символы для поиска
 * @return указатель на первое вхождение в string1 найденного символа
 *
 * Функция выполняет поиск первого вхождения в строку string1 
 * любого из символов строки string2. 
 * Возвращает указатель на первое вхождение в string1 найденного символа, 
 * или — пустой указатель, если нет ни одного совпадения. 
 * Поиск не учитывает завершающий нуль-символ. 
 */
char *my_strpbrk(const char *str1, const char *str2)
{
    for (size_t i = 0; str1[i] != '\0'; i++)
        for (size_t j = 0; str2[j] != '\0'; j++)
            if (str1[i] == str2[j])
                return (char *) &str1[i];
    return NULL;
}

/**
 * @brief Индекс конца подстроки string1, состоящей из символов string2.
 * 
 * @param string1 строка для поиска
 * @param string2 символы для поиска
 * @return char*
 *
 * Функция выполняет поиск символов строки string2 в строке string1. 
 * Возвращает длину начального участка строки string1 
 * которая состоит только из символов, которые являются частью строки string2. 
 */
size_t my_strspn(const char *string1, const char *string2)
{
    size_t i;
    for (i = 0; string1[i] != '\0'; i++)
        for (size_t j = 0; string1[i] != string2[j]; j++)
            if (string2[j] == '\0')
                return i;
    return i;
}

/**
 * @brief Индекс первого вхождения в string1 символа из string2
 * 
 * @param string1 строка для поиска
 * @param string2 символы для поиска
 * @return size_t 
 *
 * Функция strcspn выполняет поиск первого вхождения 
 * в строку string1 любого из символов строки string2, 
 * и возвращает количество символов до найденного первого вхождения.
 * Поиск учитывает и завершающий нуль-символов, поэтому, 
 * если функция возвращает длину строки string1, это значит, 
 * что ни один из символов строки string2 не входит в состав string1.
 */
size_t my_strcspn(const char *string1, const char *string2)
{
    size_t i;
    for (i = 0; string1[i] != '\0'; i++)
        for (size_t j = 0; string2[j] != '\0'; j++)
            if (string1[i] == string2[j])
                return i;
    return i;
}

/**
 * @brief Указатель на первое вхождение symbol в string
 * 
 * @param string1 строка для поиска
 * @param symbol символ для поиска
 * @return char*
 *
 * Функция strchr выполняет поиск первого вхождения символа symbol в строку string. 
 * Возвращает указатель на первое вхождение символа в строке. 
 * Завершающий нулевой символ считается частью Си-строки. 
 * Таким образом, он также может быть найден для получения указателя на конец строки. 
 */
char *my_strchr(const char *string, int symbol)
{
    size_t i;
    for (i = 0; string[i] != '\0'; i++)
        if (string[i] == symbol)
            return (char *) &string[i];
    if (string[i] == symbol)
        return (char *) &string[i]; 
    return NULL;
}

/**
 * @brief Указатель на последнее вхождение symbol в string
 * 
 * @param string1 строка для поиска
 * @param symbol символ для поиска
 * @return char*
 *
 * Функция strrchr выполняет поиск последнего вхождения символа symbol в строку string. 
 * Возвращает указатель на последнее вхождение символа в строке. 
 * Завершающий нулевой символ считается частью Си-строки. 
 * Таким образом, он также может быть найден для получения указателя на конец строки. 
 */
char *my_strrchr(const char *string, int symbol)
{
    char *c = NULL;
    size_t i;
    for (i = 0; string[i] != '\0'; i++)
        if (string[i] == symbol)
            c = (char *) &string[i];
    if (c != NULL)
        if (*c == symbol)
            return c;
    if (string[i] == symbol)
        return (char *) &string[i];
    return NULL;
}
