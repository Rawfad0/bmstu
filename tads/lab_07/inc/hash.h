/**
 * @file hash.h
 * @brief Хеш-таблица
 * 
 */

#ifndef HASH_H__
#define HASH_H__

#include <stddef.h>

typedef enum ht_error
{
    /// При выполнении действия ошибок не возникло
    HT_OK = 0,
    /// При вызове функции указаны неверные параметры
    HT_INVALID_PARAM, 
    /// При выполнении действия возникли ошибки при работе с памятью 
    HT_MEM,
    /// Не найдено значение по указанному ключу
    HT_NOT_FOUND
} ht_rc_t;

// Обратный полиномиальный хеш
// h = ( s0 * k^n + s1 * k^(n-1) + ... + s(n-1) * k + sn ) % mod
int hash(char *key, int k, int mod);

int get_prime(int old_prime);

#endif