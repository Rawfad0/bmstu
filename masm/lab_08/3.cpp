#include <iostream>
#include <assert.h>
#include <cmath>
#include <iomanip>
#include <cstdio>

// double func_cpp(double x)
// {
//     return sin(x*x + 5*x);
// }

// double bisection_method_cpp(double a, double b, double (func)(double))
// {
//     double fa = func(a);
//     double fb = func(b);
//     // double fa = func_cpp(a);
//     // double fb = func_cpp(b);
//     // std::cout << fa << "  " << fb << std::endl;
//     // std::cout << fa << " " << fb << std::endl;

//     // Неопределенное значение (необходимо, чтобы концы интервала отличались по знаку)
//     assert((fa * fb <= 0));
    
//     double fc, c;
//     do {
//         c = (a + b) / 2.0;
//         fc = func_cpp(c);
        
//         if (fa * fc < 0) {
//             b = c;
//             fb = fc;
//         } else {
//             a = c;
//             fa = fc;
//         }
//     } while (fabs(b - a) > EPS);
    
//     return (a + b) / 2.0;
// }

double func_asm(double x)
{
    double res;
    const int add = 5;
    __asm__(                    // [ - основание стека
        "fld %1\n"              // [   <-x          => [x               положить x в стек
        "fild %2\n"             // [x   <-5         => [x, 5            положить 5 в стек
        "faddp\n"               // [x, 5            => [x + 5
        "fld %1\n"              // [x + 5 <-x       => [x, x            положить x в стек
        "fmulp\n"               // [x + 5, x        => [x^2 + 5*x       умножить x и x
        "fsin\n"                // [x^2 + 5*x       => [sin(x^2 + 5x)
        "fstp %0\n"             // [sin(x^2 + 5*x)  => [ -> res    взять sin(x^2 + 5*x) из стека в res
        : "=m" (res)            // Выходной параметр
        : "m" (x), "m" (add)    // Входной параметр
        );
    // std::cout << "f(" << x << "): " << res << std::endl; 
    return res;
}

double bisection_method_asm(double a, double b, size_t iters, double (func)(double))
{
    double c;
    const int TWO = 2;
    
    double fa = func_asm(a), fb = func_asm(b), fc;
    double a_s = a, b_s = b;
        
    for (size_t i = 0; i < iters; i++)
    {
        double a_s = a, b_s = b;
        
        __asm__(
            "fld %1\n"              // a
            "fld %2\n"              // b
            "faddp\n"               // a + b, b из стека
            "fild %3\n"
            "fdivp\n"               // a + b / 2, 2 из стека
            "fstp %0\n"             // результат из стека в C
            : "=m" (c)              
            : "m" (a), "m" (b), "m" (TWO)
        );
        
        fc = func(c);
        
        __asm__(
            "fld %2\n"              // Загрузить fa в регистр ST0 (fpu stack top)
            "fld %5\n"              // Загрузить fc в ST1
            "fmulp\n"               // Умножить fa и fc, результат в ST0 и вытолкнуть ST1

            "fldz\n"                // Загрузить ноль в ST1
            "fcom\n"                // Сравнить результат с нулем и изменить флаги
            "fstsw ax\n"            // Сохранить регистр статуса FPU в AX
            "sahf\n"                // Применить флаги условия к регистру флагов процессора

            "ja greater\n"          // Если флаг C1 установлен в 0, перейти к метке greater
            "jmp less\n"            // В противном случае перейти к метке less

            "less:\n"
            "fstp %0\n"             // Обновляем a
            "fstp %1\n"             // Обновляем b
            "fld %4\n"              // Загрузить значение c
            "fstp %0\n"             // Сохранить c в a
            "fld %5\n"              // Загрузить значение fc
            "fstp %2\n"             // Сохранить в fa
            "fld %7\n"              // tmp-выгруз в b
            "fstp %1\n"
            "jmp end\n"             // Перейти к концу

            "greater:\n"
            "fstp %0\n"             // Обновляем a
            "fstp %1\n"             // Обновляем b
            "fld %4\n"              // Загрузить значение c
            "fstp %1\n"             // Сохранить c в b
            "fld %5\n"              // fc в fb 
            "fstp %3\n"
            "fld %6\n"              // a_s в a
            "fstp %0\n"

            "end:\n"
            : "=m" (a), "=m" (b), "=m" (fa), "=m" (fb)   // a, b
            : "m" (c), "m" (fc), "m" (a_s), "m" (b_s)    // c, fc
            : "%ax"
        );
        if (fc == 0)
            return c;
        // std::cout << " a: " << a << " fa: " << fa << "; b : " << b << " fb: " << fb << std::endl;
    }
    return c;
}

// double bisection_method_asm2(double a, double b, size_t iters, double (func)(double))
// {
//     double c;
//     const int TWO = 2;
//     for (size_t i = 0; i < iters; i++)
//     {
//         double fa = func_asm(a), fb = func_asm(b), fc;
//         double a_tmp = a, b_tmp = b;
        
//         __asm__(
//             "fld %4\n"
//             "fld %5\n"
//             "faddp\n"
//             "fild %6\n"
//             "fdivp\n"
//             "fstp eax\n"            // a+b/2 -> EAX

//             "push eax\n"
//             "call func\n"
//             "add esp,4\n"
//             // "fstp "

//             "fld %2\n"              // Загрузить fa в ST0
//             "fld ebx\n"             // Загрузить fc в EBX
//             "fmulp\n"               // fa * fc в ST0 и вытолкнуть ST1

//             "fldz\n"                // 0 в ST1
//             "fcom\n"                // Сравнить fa*fc с 0 и изменить флаги
//             "fstsw ecx\n"           // Сохранить регистр статуса FPU в AX
//             "sahf\n"                // Применить флаги условия к регистру флагов процессора

//             "ja greater\n"          // Если флаг C1 установлен в 0, перейти к метке greater
//             "jmp less\n"            // В противном случае перейти к метке less

//             "less:\n"
//             "fstp %0\n"             // -> a
//             "fstp %1\n"             // -> b
//             "fld eax\n"             // <- c
//             "fstp %0\n"             // c -> a
//             "fld ebx\n"             // <- fc
//             "fstp %2\n"             // fc -> fa
//             "fld %5\n"              // <- b
//             "fstp %1\n"             // b -> b
//             "jmp end\n"

//             "greater:\n"
//             "fstp %0\n"             // -> a
//             "fstp %1\n"             // -> b
//             "fld eax\n"             // <- c
//             "fstp %1\n"             // c -> b
//             "fld ebx\n"             // <- fc  
//             "fstp %3\n"             // fc -> fb
//             "fld %4\n"              // <- a
//             "fstp %0\n"             // a -> a

//             "end:\n"
//             : "=m" (a), "=m" (b), "=m" (fa), "=m" (fb) 
//             : "m" (a_tmp), "m" (b_tmp), "m" (TWO)
//             : "%eax", "%ebx", "%ecx"
//         );
//         std::cout << " a: " << a << " fa: " << fa << "; b : " << b << " fb: " << fb << std::endl;
//     }
//     return (a + b) / 2.0;
// }

int main()
{
    double a;
    double b;
    size_t iters;
    std::cin >> a >> b >> iters;
    // double a = -0.2;
    // double b = 0.2;
    // size_t iters = 100;

    double (*p_func_asm)(double) = &func_asm;

    printf("    \nFunction:      f(x) = sin(x^2 + 5*x)\n");
    
    double root = bisection_method_asm(a, b, iters, p_func_asm);
    std::cout << std::setprecision(20) << root << std::endl;
    
    return 0;
}