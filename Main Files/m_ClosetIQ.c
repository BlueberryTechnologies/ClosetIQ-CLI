/*
ClosetIQ-CLI
Blueberry Technologies
Riley Richard (gh/rileyrichard)
This will be a project to get the basic functionality of the program.

Synopsis:
Virtual Closet which you can organize, view, and modify various types of clothing.
Closet is viewable and modifiable through the terminal.
Closet information is stored in the user's home folder, or document folder depending on operating system.
*/

#include "m_ClosetIQ.h"
#include "../Functions/add.c"
#include "../Functions/modify.c"
#include "../Functions/remove.c"
#include "../Functions/systemFunctions.c"

/*
Functions
*/



/*
Menu Functions
*/
void userMenu()
{
    printf("==============================================\n");
    printf("%39s\n", "ClosetIQ (Command Line Version!)");
    printf("%38s\n\n", "Made by Blueberry Technologies");
    printf("1.) View the current closet.\n");
    printf("2.) Modify the current closet.\n");
    printf("3.) Choose an outfit (Coming Soon!)\n");
    printf("4.) Delete the current closet.\n");
    printf("5.) Exits the program.\n");
    printf("==============================================\n");
    printf("> ");
    int userChoice;
    scanf("%d", &userChoice);

    switch (userChoice)
    {
    case 1:
        viewCloset();
        break;
    case 2:
        modifyClosetMenu();
        break;
    case 3:
        getLatestIndex();
        break;
    case 4:
        removeCloset();
        break;
    case 5:
        exit(EXIT_SUCCESS);
    default:
        printf("That choice was not allowed.\n");
        userMenu();
        break;
    }
}
void modifyClosetMenu()
/*
Allows the user to modify their closet. Add, remove, and change operations for the items within.
*/
{
    int userModifyInput;
    printf("==============================================\n");
    printf("%39s\n", "ClosetIQ (Command Line Version!)");
    printf("%30s\n\n", "Modify Closet.");
    printf("What would you like to do?\n");
    printf("1.) Add items to the closet.\n");
    printf("2.) Change existing items in the closet.\n");
    printf("3.) Return to the menu.\n");
    printf("==============================================\n");
    printf("> ");
    scanf("%d", &userModifyInput);

    switch (userModifyInput)
    {
    case 1:
    {
        addClothesToCloset();
        break;
    }
    case 2:
    {
        modifyIndex();
        pressEnter();
        break;
    }
    case 3:
    {
        userMenu();
        break;
    }
    default:
    {
        printf("That value was not allowed.\n");
        modifyClosetMenu();
        break;
    }
    }
}


/*
Closet Functions
*/

void viewCloset()
/*
Shows the user's closet and current formatting.
*/
{
    char *path = returnSavePath(0);

    if (path == NULL)
    {
        fprintf(stderr, "The path was not found.\n");
        return;
    }
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open the closet.\n");
        return;
    }
    char typeOfClothes[100];
    char colorOfClothes[100];
    int quantity;
    int index;
    bool thingsInCloset = false;
    printf("\n\n\n=============================================================\n");
    printf("%-10s %-20s %-20s %s\n", "Index", "Type of Clothes", "Color of Clothes", "Quantity");
    printf("=============================================================\n");
    while (fscanf(file, "%d %99s %99s %d", &index, typeOfClothes, colorOfClothes, &quantity) == 4)
    {
        printf("%-10d %-20s %-20s %d\n", index, typeOfClothes, colorOfClothes, quantity);
        thingsInCloset = true;
    }

    if (!thingsInCloset){
        printf("%41s", "The closet is empty!\n");
    }
    char userConfirmation;
    fclose(file);
    free(path);
    printf("=============================================================\n");
    pressEnter();
}



int main(){
    char *path = returnSavePath(0);
    userMenu();
}