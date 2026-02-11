#include <stdio.h>
#include <time.h>
#include <iostream>
#include <chrono>

#define REPEAT 1e7

template <typename T>
void cpp_measure_time(int rep, T a, T b)
{
    T res;
    std::chrono::duration<double> time_sum(0);
    std::chrono::duration<double> time_mul(0);

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < rep; ++i)
        res = a + b;
    time_sum = std::chrono::high_resolution_clock::now() - start;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < rep; ++i)
        res = a * b;
    time_mul = std::chrono::high_resolution_clock::now() - start;

    std::cout << time_sum.count() << " " << time_mul.count() << std::endl;
}

template <typename T>
void asm_measure_time(int rep, T a, T b)
{
    T res;
    std::chrono::duration<double> sum_time(0);
    std::chrono::duration<double> mul_time(0);

    // Сложение на асемблере
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < rep; ++i)
        __asm__("fld %1\n"              // загружаем a в стек
                "fld %2\n"              // загружаем b в стек
                "faddp\n"               // складываем A и B в A затем выбросить B из стека
                "fstp %0\n"             // извлекаем число A из FPU в память (res)
                : "=m"(res)
                : "m"(a),
                  "m"(b)
                );
    sum_time = std::chrono::high_resolution_clock::now() - start;

    // Умножение на асемблере
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < rep; ++i)
        __asm__("fld %1\n"
                "fld %2\n"
                "fmulp\n"
                "fstp %0\n"
                : "=m"(res)
                : "m"(a),
                  "m"(b)
                );
    mul_time = std::chrono::high_resolution_clock::now() - start;

    std::cout << sum_time.count() << " " << mul_time.count() << std::endl;
}

// -DASM параметр
#ifdef ASM
#define TIME_MEASURE(T) asm_measure_time<T>
#else
#define TIME_MEASURE(T) cpp_measure_time<T>
#endif

enum rc
{
    OK = 0
};

int main()
{
    double a = -1.1, b = 1234.5;
    printf("       SUM       MUL\n");
    printf("FLOAT  ");
    TIME_MEASURE(float)(REPEAT, a, b);
    printf("DOUBLE ");
    TIME_MEASURE(double)(REPEAT, a, b);

    return OK;
}