#include <stdio.h>
int main()
{
    int x;
    float y;
    unsigned short int array[] = {1, 2, 3};
    void *pV;
    unsigned char *pUC;
    int i;
    pV = &x;
    *((int *) pV) = 12;
    printf("pV as int:%d\n", *((int *) pV));
    pV = &y;
    *((float *) pV) = 123.24f;
    printf("pV as float:%f\n", *((float *) pV));
    pV = array;
    pUC = (unsigned char *) pV;
    for (i=0; i <sizeof(array) / sizeof(unsigned char); i++)
    {
        // works fine
        printf("pUC %d:%.2X\n", i, *pUC);
        pUC++;

        /* works fine
        printf("pUC %d:%.2X\n", i, * (unsigned char *) pV);
        pV++;

        Doesn't work: error: invalid use of void expression
        printf("pUC %d:%.2X\n", i, *pV);
        pV++;
        */
    }
    return 0;
}