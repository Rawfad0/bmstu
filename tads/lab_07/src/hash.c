#include "hash.h"
#include "math.h"


int hash(char *key, int k, int mod)
{
    int hash = 0;
    for (char *ch = key; *ch != '\0'; ch++)
        hash = (hash * k + (*ch - 'a')) % mod;
    return hash;
}

int is_prime(int num)
{
    int nr = sqrt(num);
    for (int i = 2; i <= nr; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

int get_prime(int old_prime)
{
    int res = 2;
    while (res <= old_prime || is_prime(res) != 1)
        res += 1;
    return res;
}