#include <iostream>

using namespace std;

double sin_asm(auto rad)
{
    double res;

    __asm__(
        "fld %1\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res)
        : "m"(rad)
    );

    return res;
}

double sin_pi()
{
    double res;

    __asm__(
        "fldpi\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res)
    );

    return res;
}

double sin_half_pi()
{
    double res;
    const double two = 2.0;

    __asm__(
        "fldpi\n"
        "fld %1\n"
        "fdivp\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res)
        : "m"(two)
    );

    return res;
}

int main()
{
    const double pi1 = 3.14;
    const double pi2 = 3.141596;

    cout << "pi = " << pi1 << endl;
    cout << sin_asm(pi1) << endl;
    cout << sin_asm(pi1 / 2.0) << endl;

    cout << "pi = 3.141596" << endl;
    cout << sin_asm(pi2) << endl;
    cout << sin_asm(pi2 / 2.0) << endl;

    cout << "asm pi:" << endl;
    cout << sin_pi() << endl;
    cout << sin_half_pi() << endl;
    return 0;
}
