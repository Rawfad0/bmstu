#include <stdio.h>
#include <string.h>

int main(void)
{
    char b[32];
    strcpy(b, "123456789012345");
    printf("[%s]\n", b);
    strcpy(b+1, b);
    printf("[%s]\n", b);

    return 0;
}