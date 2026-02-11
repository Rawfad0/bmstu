#include <stdio.h>

#define N 30

void func_solve_clean(int a[N], int b[N], int n)
{
    // Поиск максимума
    int max = a[0];                 // 2
    for (int i = 0; i < n; i++)
        if (a[i] > max)
            max = a[i];

    // Проверка на особый случай
    int i = n - 1;
    for (; i >= 0 && a[i] == max; i--);
    if (i == -1)
        printf("Особый случай: X отсутствует, т.к. все элементы максимальные.");

    // Поиск самого правого ближайшего по модулю к максимальному
    int xi = i; // i - первый с конца немаксимальный элемент      
    int abs_max = max > 0 ? max : -max;
    int abs_ai = a[i] > 0 ? a[i] : -a[i];
    int d = abs_ai - abs_max;         // 3
    int min_d = d > 0 ? d : -d; // 3-4
    for (; i >= 0; i--)
    {
        int abs_ai = a[i] > 0 ? a[i] : -a[i];
        int d = abs_ai - max;         // 3
        int abs_d = d > 0 ? d : -d; // 3-4
    
        if (a[i] != max && abs_d < min_d)
        {
            min_d = abs_d;
            xi = i;
        }
    }
    // xi - индекс искомого числа

    // Копирование в массив B
    int j = 0;
    for (int i = 0; i < xi; i++)
    {
        if (a[i] > 0 && a[i] % 8 == 0)
        {
            b[j] = a[i];
            j++;
        }
    } 
    
    // Удаление
    i = 0;
    j = 0;
    // слева от x отрицательных чисел  
    for (; i < xi; i++)
    {
        if (a[i] >= 0)
        {
            a[j] = a[i];
            j++;
        }
    }
    // сам x оставляем
    a[j] = a[i];
    i++;
    j++;
    // справа от x чисел > 0 и %8 == 0
    for (; i < n; i++)
    {
        if (a[i] <= 0 || a[i] % 8 != 0)
        {
            a[j] = a[i];
            j++;
        }
    }
}

int func_solve(int a[N], int b[N], int n)
{
    int res = 0;
    int t_res = 0;

    // Поиск максимума
    int max = a[0];                 // 2
    res += 2;
    
    res += 2;   // цикл
    for (int i = 0; i < n; i++)
    {
        res += 2; // цикл
        res += 2; // усл
        if (a[i] > max)
        {
            max = a[i];
            res += 2;
        }
    }
    // printf("max=%d\n", max);
    printf("max cost = %d\n", res);
    t_res = res;

    // Проверка на особый случай
    int i = n - 1;
    res += 2;
    res += 4;
    for (; i >= 0 && a[i] == max; i--)
        res += 5;
    res += 1;
    if (i == -1)
        printf("Особый случай: X отсутствует, т.к. все элементы максимальные.");

    printf("check cost = %d\n", res - t_res);
    t_res = res;

    // printf("i=%d\n",i);
    // Поиск самого правого ближайшего по модулю к максимальному
    int xi = i; // i - первый с конца немаксимальный элемент  
    res += 1;

    int abs_ai = a[i] > 0 ? a[i] : -a[i];
    res += a[i] > 0 ? 4 : 5;

    int abs_max = max > 0 ? max : -max;
    res += max > 0 ? 2 : 3;

    int d = abs_ai - abs_max;         // 3
    res += 2;

    int min_d = d > 0 ? d : -d; // 3-4
    res += d > 0 ? 2 : 3;

    res += 1;
    for (; i >= 0; i--)
    {
        res += 2;

        int abs_ai = a[i] > 0 ? a[i] : -a[i];
        res += a[i] > 0 ? 4 : 5;

        int d = abs_ai - max;         // 3
        res += 2;
        int abs_d = d > 0 ? d : -d; // 3-4
        res += d > 0 ? 3 : 4;

        res += 4;
        if (a[i] != max && abs_d < min_d)
        {
            min_d = abs_d;
            xi = i;
            res += 2;
        }
        // printf("ai=%d; abs_d=%d; min_d=%d; ax=%d\n", a[i], abs_d, min_d, a[xi]);
    }
    printf("x cost = %d\n", res - t_res);
    t_res = res;
    // xi - индекс искомого числа

    
    // printf("xi=%d\n", xi);
    // printf("a[xi]=%d\n", a[xi]);
    
    // Копирование в массив B
    int j = 0;
    res += 1;
    res += 2;
    for (int i = 0; i < xi; i++)
    {
        res += 2;
        res += 7;
        if (a[i] > 0 && a[i] % 8 == 0)
        {
            b[j] = a[i];
            j++;
            res += 4;
        }
    }
    printf("copy cost = %d\n", res - t_res);
    t_res = res;

    // Удаление
    i = 0;
    j = 0;
    res += 2;
    // слева от x отрицательных чисел  
    res += 1;
    for (; i < xi; i++)
    {
        res += 2;
        res += 2;
        if (a[i] >= 0)
        {
            a[j] = a[i];
            j++;
            res += 4;
        }
    }
    // сам x оставляем
    a[j] = a[i];
    i++;
    j++;
    res += 5;
    // справа от x чисел > 0 и %8 == 0
    res += 1;
    for (; i < n; i++)
    {
        res += 2;
        res += 7;
        if (a[i] <= 0 || a[i] % 8 != 0)
        {
            a[j] = a[i];
            j++;
            res += 4;
        }
    }
    printf("del cost = %d\n", res - t_res);
    t_res = res;

    return res;
}

void test_1(void)
{    
    int a[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[N] = { 0 };
    int n = 11;

    int res = func_solve(a, b, n);
    printf("1) res=%d\n\n", res);
}

void test_2(void)
{    
    int a[N] = { 4, -8, 8, 5, 4, 4, 0, -1, 4, 4, 6};
    int b[N] = { 0 };
    int n = 11;

    int res = func_solve(a, b, n);
    printf("2) res=%d\n\n", res);
}

void test_3(void)
{    
    int a[N] = { 9, 1, 2, 3, 4, 5, 0, 1, -1, -3, -4};
    int b[N] = { 0 };
    int n = 11;

    int res = func_solve(a, b, n);
    printf("3) res=%d\n\n", res);
}

void test_4(void)
{    
    int a[N] = { 8, 9, 1, 2, 3, 4, 5, 0, 1, -1, -3};
    int b[N] = { 0 };
    int n = 11;

    int res = func_solve(a, b, n);
    printf("4) res=%d\n\n", res);
}

void test_5(void)
{    
    int a[N] = { 9, 8, 1, 2, 3, 4, 5, 0, 1, -1, -3};
    int b[N] = { 0 };
    int n = 11;

    int res = func_solve(a, b, n);
    printf("5) res=%d\n\n", res);
}

void test_6(void)
{
    int a[N] = { -8, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1};
    int b[N] = { 0 };
    int n = 11;

    int res = func_solve(a, b, n);
    printf("6) res=%d\n\n", res);
}


void test_7(void)
{
    int a[N] = { -8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    int b[N] = { 0 };
    int n = 11;

    int res = func_solve(a, b, n);
    printf("7) res=%d\n\n", res);
}

int main(void)
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    // test_8();
    
    return 0;
}
