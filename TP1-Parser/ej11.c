#include <stdio.h>
int main(void)
{
    int a = 0, b = 1, c = 2;
    void *p;
    a = 256;
    b = 257;
    c = 258;
    p = &a;
    char ch1 = *((char *) p);
    p = &b;
    char ch2 = *((char *) p);
    p = &c;
    char ch3 = *((char *) p);
    // '0' Offest tabla askii
    printf("a:%c b:%c c:%c\n", ch1 + '0', ch2 + '0', ch3 + '0');
    return 0;
}