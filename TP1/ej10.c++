#include <stdio.h>
int main(void)
{
    char a = 'h';
    void *p;
    p = &a;
    /* Doing
    printf("a:%c\n", *p);
    wount work cause p is not a poitner object type, it a void pointer
    the correct sintax would be:
    */
    printf("a:%c\n", * (char*) p);
    /* cast the proper pointer data type and then desrreference it*/
    return 0;
}