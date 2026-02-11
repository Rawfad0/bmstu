#include <iostream>
extern "C"
{
    void testAsm(); // подключение в код на Си/Си++ функции
                    // на другом языке программирования,
                    // выполненной в соответствии с соглашениями
                    // о вызовах Си
}

int main()
{
    int i = 0;
    __asm__("mov eax, 5\n"
            "mov %0, eax\n"
            : "=r"(i)
            : "r"(i)
            : "%eax"
            );
    std::cout << i;
    // testAsm();
    // __asm {
    //     mov i, eax;
    // }
    // std::cout << i;
    return 0;
}