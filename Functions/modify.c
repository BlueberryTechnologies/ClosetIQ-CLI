#include "../Main Files/m_ClosetIQ.h"
/*
Functions
*/


void modifyIndex(){
    printf("What is the index you would like to modify?\n> ");
    modifyIndexMenu(atoi(getUserInput()));
}


void modifyIndexMenu(int userIndex){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    char *modifyIndexChoice = malloc(MAX_USER_ENTERABLE_SIZE);
    printf("==============================================\n");
    printf("%39s\n", "ClosetIQ (Command Line Version!)");
    printf("%29s %i\n\n", "Modified index:", userIndex);
    printf("1.) Change index.\n");
    printf("2.) Remove index from closet.\n");
    printf("3.) Return to main menu.\n");
    printf("==============================================\n");
    printf("> ");
    
    if (fgets(modifyIndexChoice, 255, stdin))
    {
        modifyIndexChoice[strcspn(modifyIndexChoice, "\n")] = 0;
    }

    int selectedChoice = atoi(modifyIndexChoice);

    switch(selectedChoice){
        case 1:
            break;
        case 2:
            removeItem(userIndex);
        case 3:
            pressEnterOther();
        default:
            printf("I'm sorry that value was not allowed. Try again");
            pressEnter();
    }
}