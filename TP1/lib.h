#include<stdlib.h>

typedef int (*pCallback) (char*, char*, void*);

int parseCmdLine(int argc, char* argv[], pCallback p, void* userData);

