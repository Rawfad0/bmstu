#include "palindrome.h"

bool sa_is_palindrome(sa_stack_t *word, size_t word_len)
{
    sa_stack_t rev_word =  { { '\0' }, NULL, NULL };
    rev_word.pe = rev_word.array + MAX_ARR_LEN;
    rev_word.sp = rev_word.array;
    // Деление
    for (size_t i = 0; i != word_len / 2; i++)
    {
        char ch;
        sa_pop(word, &ch);
        sa_push(&rev_word, ch);
    }
    // Если нечетный, то средний элемент не влияет
    char middle = '\0';
    if (word_len % 2 != 0)
        sa_pop(word, &middle);
    // Проверка на палиндром
    for (size_t i = 0; i != word_len / 2; i++)
    {
        char word_ch, rev_word_ch;
        sa_pop(word, &word_ch);
        sa_pop(&rev_word, &rev_word_ch);

        if (word_ch != rev_word_ch)
            return false;
    }

    return true;
}

bool ll_is_palindrome(ll_stack_t *word, size_t word_len)
{
    bool flag = true;
    ll_stack_t rev_word = {NULL};
    // Деление
    for (size_t i = 0; i != word_len / 2; i++)
    {
        list_t *tmp;
        ll_pop(word, &tmp);
        ll_push(&rev_word, &tmp->value);
        free(tmp);
    }
    // Если нечетный, то средний элемент не влияет
    list_t *middle;
    if (word_len % 2 != 0)
        ll_pop(word, &middle);
    // Проверка на палиндром
    for (size_t i = 0; i != word_len / 2; i++)
    {
        list_t *word_ch, *rev_word_ch;
        ll_pop(word, &word_ch);
        ll_pop(&rev_word, &rev_word_ch);

        if (flag == true && word_ch->value != rev_word_ch->value)
            flag = false;
        free(word_ch);
        free(rev_word_ch);
    }

    return flag;
}