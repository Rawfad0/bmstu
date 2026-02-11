#include <iostream>

extern "C"
{
    char *asm_strncpy(char *dst, const char *src, size_t n);
}

size_t mystrlen(const char *str)
{
    size_t len = 0;

    __asm__("mov ecx, -1\n\t"
            "mov edi, %1\n\t"
            "mov al, 0\n\t"
            "repne scasb\n\t"
            "neg ecx\n\t"
            "sub ecx, 2\n\t"
            "mov %0, ecx\n\t"
            : "=r" (len)
            : "r" (str)
            : "ecx", "edi", "al"
            );

    return len;
}

int main()
{
    char* str = new char[6];
    asm_strncpy(str, "abc", 3);
    asm_strncpy(str+1, str, 3);
    std::cout << str << std::endl;

    delete[] str;
    // const char* src = "aba";
    // size_t l = mystrlen(src);
    // char* dst = new char[4];
    // dst[3] = '\0';

    // asm_strncpy(dst, src, 4);

    // std::cout << dst << std::endl;
    // std::cout << l << std::endl;

    // delete[] dst;
    return 0;
}
