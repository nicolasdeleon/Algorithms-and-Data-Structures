#include <stdio.h>
#include <stdlib.h>

// Callback functions
float doSum(float a, float b)
{
    printf("Doing %f + %f\n", a, b);
    return a + b;
}
float doRes(float a, float b)
{
    printf("Doing %f - %f\n", a, b);
    return a - b;
}
float doMul(float a, float b)
{
    printf("Doing %f * %f\n", a, b);
    return a * b;
}
float doDiv(float a, float b)
{
    printf("Doing %f / %f\n", a, b);
    return a / b;
}

// Type definitions
typedef float (*OperationCallback)(float a, float b);

void runOperation(int *isCalcRunning, float op1, float op2, char *title, char **label, OperationCallback *callback, int size)
{
    int i;
    unsigned int selectedItem;

    // Print title
    printf("%s\n", title);

    // Print operation options
    for (i= 0; i < size; i++)
        printf("%d: %s\n", i + 1, label[i]);
    
    // Get option, max input string to 16
    char buffer[16];
    printf("> ");
    fgets(buffer, sizeof(buffer), stdin);

    // Call callback
    selectedItem = atoi(buffer) - 1;

    if (selectedItem > size)
    {
        printf("Invalid entry.\n");
        return;
    }
    else if (callback[selectedItem])
    {
        printf("Result = %.2f\n", callback[selectedItem](op1, op2));
        return;
    }
    else
    {
        *isCalcRunning = 0;
        printf("\n");
        return;
    }

}

int main()
{
    float op1;
    float op2;
    char *operatonLabel[] = {
        "+",
        "-",
        "*",
        "/",
        "quit"
        };
    float (*operationCallback[])(float a, float b) = {
        doSum,
        doRes,
        doMul,
        doDiv,
        NULL
        };

    int isCalcRunning = 1;

    while(isCalcRunning)
    {
    //Get options
    char buffer[16];
    printf("Operator 1: ");
    fgets(buffer, sizeof(buffer), stdin);
    op1 = atof(buffer);
    printf("%.2f\n", op1);

    printf("Operator 2: ");
    fgets(buffer, sizeof(buffer), stdin);
    op2 = atof(buffer);
    printf("%.2f\n", op2);

    runOperation(&isCalcRunning, op1, op2, "Choose Operation", operatonLabel, operationCallback,
    sizeof(operationCallback) / sizeof(OperationCallback));
    }

    return 0;

}