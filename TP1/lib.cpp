#include "lib.h"

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData) {

    int argumentCounter = 0;
    int ok;
    char * param;
    char * value;

    for (int i = 1; i<argc; i++)
    {
        param = argv[i];

        /* If encountered an key, next argument is a value. If value is NULL then returning error */
        if (param[0]=='-')
        {
            if (param[1] != '\0')
            {
                argumentCounter++; // increment counter by 1 option
                i++;
                value = argv[i];
                if (value == NULL)
                {
                    return -1;
                }
                ok = p(param, value, userData);
            }
            else
            {
                ok = 0;
            }
        }
        else
        {
            argumentCounter++; // increment counter by 1 param
            ok = p(NULL, param, userData);
        }

        /* Check callback validity */
        if (!ok)
        {
            return -1;
        }

    }
    return argumentCounter;
}