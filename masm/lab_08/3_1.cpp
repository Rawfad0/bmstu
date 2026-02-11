#include <iostream>

extern "C"
{
    double root(double a, double b, size_t count);
}

int main()
{
    double a;
    double b;
    size_t iters;
    std::cin >> a >> b >> iters;

    double res = root(a, b, iters);

    std::cout << res << std::endl;

    return 0;
}