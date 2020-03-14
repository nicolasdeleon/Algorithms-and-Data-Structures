#include <stdio.h>
#include <stdlib.h>

// Callback functions
void doFile()
{
    printf("File menu selected.\n");
}
void doEdit()
{
    printf("Edit menu selected.\n");
}
void doView()
{
    printf("View menu selected.\n");
}

// Type definitions
typedef void (*MenuCallback)(); // CONSULTAR

void runMenu(char *title, char **label, MenuCallback *callback, int size)
{
    int isMenuRunning = 1;
    int i;
    unsigned int selectedItem;
    while(isMenuRunning)
    {
        // Print menu
        printf("%s\n", title);
        for (i= 0; i < size; i++)
            printf("%d: %s\n", i + 1, label[i]);
        // Get option
        char buffer[16];
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);
        // Call callback
        selectedItem = atoi(buffer) - 1;

        /*
        fgets: https://www.educative.io/edpresso/how-to-use-the-fgets-function-in-c?https://www.educative.io/courses/grokking-the-object-oriented-design-interview?aid=5082902844932096&utm_source=google&utm_medium=cpc&utm_campaign=blog-dynamic&gclid=EAIaIQobChMIgN7F76Ka6AIVjIaRCh3PRg26EAAYASAAEgJDp_D_BwE
        atoi: https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm
        */

        if (selectedItem > size)
            printf("Invalid entry.\n");
        else if (callback[selectedItem])
            callback[selectedItem]();
        else
            isMenuRunning = 0;
        printf("\n");
    }
}

int main()
{
    char *menuLabel[] = {
        "File",
        "Edit",
        "View",
        "Quit"
        };
    void (*menuCallback[])(void) = {
        doFile,
        doEdit,
        doView,
        NULL
        };
    runMenu("Main Menu", menuLabel, menuCallback,
    sizeof(menuCallback) / sizeof(MenuCallback));
    return 0;
}