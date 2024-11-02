#include "my_snprintf.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

// Увеличение интератора по строке формата на размер простого спецификатора "%s" или "%c"
#define FORMAT_SIMPLE_SPEC_INCREMENT 2
#define NUM_STR_LEN 20

void s_spec(char *s, char *str, size_t n, size_t *s_counter, size_t *format_counter, size_t *res)
{
    size_t str_len = 0;
    for (; str[str_len] != '\0'; str_len++);

    if (n == 0);
    else if (*s_counter + str_len + 1 > n)
        memcpy(s + *s_counter, str, n - 1 - *s_counter), *s_counter = n - 1;
    else
        memcpy(s + *s_counter, str, str_len), *s_counter += str_len;
    *format_counter += FORMAT_SIMPLE_SPEC_INCREMENT;
    *res += str_len;
}

void c_spec(char *s, char ch, size_t n, size_t *s_counter, size_t *format_counter, size_t *res)
{
    if (*s_counter + 1 < n)
        s[(*s_counter)++] = ch;
    *format_counter += FORMAT_SIMPLE_SPEC_INCREMENT;
    ++*res;
}

int num_to_str(int num, char num_str[NUM_STR_LEN])
{
    size_t str_len = 0;
    int negative = 0;

    if (num == 0)
        num_str[str_len++] = '0';
    if (num < 0)
        negative = 1;
    while (num != 0)
    {
        num_str[str_len++] = '0' + abs(num % 10);
        num /= 10;
    }
    if (negative)
        num_str[str_len++] = '-';

    return str_len;
}

void d_spec(char *s, int num, size_t n, size_t *s_counter, size_t *format_counter, size_t *res)
{
    char num_str[NUM_STR_LEN] = "";  // число записывается наоборот: 123 -> "321"
    size_t str_len = num_to_str(num, num_str);

    if (n == 0);
    else if (*s_counter + str_len + 1 > n)
    {
        for (size_t i = 0; *s_counter + i < n - 1; i++)
            s[*s_counter + i] = num_str[str_len - i - 1];
        *s_counter = n - 1;
    }
    else
    {
        for (size_t i = 0; i < str_len; i++)
            s[*s_counter + i] = num_str[str_len - i - 1];
        *s_counter += str_len;
    }
    *format_counter += FORMAT_SIMPLE_SPEC_INCREMENT;
    *res += str_len;
}

void no_spec(char *s, char ch, size_t n, size_t *s_counter, size_t *format_counter, size_t *res)
{
    if (*s_counter + 1 < n)
        s[(*s_counter)++] = ch;
    ++*format_counter;
    ++*res;
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    size_t res = 0;
    if (format == NULL);
    else
    {
        size_t format_len = 0;
        for (; format[format_len] != '\0'; format_len++);
        
        va_list vl;
        va_start(vl, format);

        size_t s_counter = 0, format_counter = 0;
        while (format_counter < format_len)
            if (format[format_counter] == '%' && format_len - format_counter != 1 && format[format_counter + 1] == 's')
                s_spec(s, va_arg(vl, char *), n, &s_counter, &format_counter, &res);
            else if (format[format_counter] == '%' && format_len - format_counter != 1 && format[format_counter + 1] == 'c')
                c_spec(s, va_arg(vl, int), n, &s_counter, &format_counter, &res);
            else if (format[format_counter] == '%' && format_len - format_counter != 1 && format[format_counter + 1] == 'd')
                d_spec(s, va_arg(vl, int), n, &s_counter, &format_counter, &res);
            else
                no_spec(s, format[format_counter], n, &s_counter, &format_counter, &res);
        if (n != 0)
            s[s_counter] = '\0';
        va_end(vl);
    }
    return res;
}
