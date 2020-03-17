#include "lib.h"
#include <stdio.h>

int parseCallback(char* key, char* value, void* userData){
    return 1;
}

typedef struct {
    // TODO: COMPLETE WITH USER STRCUCTURE FOR TESTING
} arg_struct;

int main (int argc, char *argv[]) {

    arg_struct userData;

    int result = parseCmdLine(argc, argv, parseCallback, &userData);

    printf("Result = %d\n", result);
    if (result == -1 )
    {
        printf("Parsing Error!\n");
    }
    return 0;
}
