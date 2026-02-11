#include <iostream>

extern "C"
{
    double root(double a, double b, size_t count);
}

int main()
{
    double beg;
    double end;
    size_t iters;
    std::cin >> beg >> end >> iters;

    double res = root(-0.1, 0.1, 10000);

    std::cout << res << std::endl;

    return 0;
}