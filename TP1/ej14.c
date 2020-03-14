#include <stdio.h>
void pointerExchange(void **a, void **b) {
    void *temp;
    temp = *a;
    *a = *b;
    *b = *temp;
    return;
}

int main() {
    int a = 5;
    char b = "h";
    char *pb = &b;
    int *pa = &a;
    void **ppa = &pa;
    void **ppb = &pb;
    pointerExchange(ppa, ppb);
    printf("now pa points to string: %c, and pb points to int: %d\n", *pa, *pb);
    return 0;
}