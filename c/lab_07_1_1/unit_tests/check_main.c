#include "check_funcs.h"

int main(void)
{
    int counter = 0;

    counter += module_test_compare_int();
    counter += module_test_mysort();

    return counter;
}