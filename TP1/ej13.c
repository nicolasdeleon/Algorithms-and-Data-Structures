#include <stdio.h>
int main(void)
{
    int a = 5;
    void *p = &a;
    void **pp = &p; // pp -> p -> a -> 5
    printf("pp:%p\n", pp);
    printf("*pp:%p\n", *pp);
    // printf("**pp:%d", **pp); // This doesnt work cause void pointer needs casting
    printf("**pp:%d", *((int *)*pp)); // only casts the p -> a pointer.
    return 0;
}