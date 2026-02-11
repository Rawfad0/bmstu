#include <iostream>
#include <ctime>

const size_t repeat_count = 1e7;

using namespace std;

void time_test_cpp(size_t times, auto a, auto b)
{
    common_type_t<decltype(a), decltype(b)> res;

    auto start = clock();
    for (size_t i = 0; i < times; ++i)
        res = a + b;
    auto time_sum = clock() - start;

    start = clock();
    for (size_t i = 0; i < times; ++i)
        res = a * b;
    auto time_mul = clock() - start;

    cout << "Sum: " << time_sum << "ms" << endl;
    cout << "Mul: " << time_mul << "ms" << endl;
}

void time_test_asm(size_t times, auto a, auto b)
{
    common_type_t<decltype(a), decltype(b)> res;

    auto start = clock();
    for (size_t i = 0; i < times; ++i)
            __asm__("fld %1\n"
            "fld %2\n"
            "faddp \n"
            "fstp %0\n"
            : "=m"(res)
            : "m"(a),
              "m"(b));
    auto time_sum = clock() - start;

    start = clock();
    for (size_t i = 0; i < times; ++i)
        __asm__("fld %1\n"
            "fld %2\n"
            "fmulp \n"
            "fstp %0\n"
            : "=m"(res)
            : "m"(a),
              "m"(b));
    auto time_mul = clock() - start;

    cout << "Sum: " << time_sum << "ms" << endl;
    cout << "Mul: " << time_mul << "ms" << endl;
}

int main()
{
    float a = -1.23;
    float b = 123.4;

    cout << "cpp:" << endl;
    cout << "prepearing: " << endl;
    time_test_cpp(repeat_count, a, b);

    cout << "float: " << endl;
    time_test_cpp(repeat_count, a, b);

    cout << "double: " << endl;
    time_test_cpp(repeat_count, static_cast<double>(a), static_cast<double>(b));

    cout << "asm:" << endl;
    cout << "prepearing: " << endl;
    time_test_asm(repeat_count, a, b);
    
    cout << "float: " << endl;
    time_test_asm(repeat_count, a, b);

    cout << "double: " << endl;
    time_test_asm(repeat_count, static_cast<double>(a), static_cast<double>(b));

    return 0;
}
