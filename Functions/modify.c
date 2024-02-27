#include "../Main Files/m_ClosetIQ.h"
/*
Functions
*/

int userIndex;


void modifyIndex(){
    clearUserInput();
    clearBuffer();
    printf("What is the index of clothing?\n> ");
    setUserInput();
    userIndex = atoi(getUserInput());
    printf("Press ENTER to continue.");
    modifyIndexMenu(userIndex);
}


void modifyIndexMenu(int userIndex){
    clearBuffer();

    printf("==============================================\n");
    printf("%39s\n", "ClosetIQ (Command Line Version!)");
    printf("%29s %i\n\n", "Modified index:", userIndex);
    printf("1.) Swap index.\n");
    printf("2.) Remove index from closet.\n");
    printf("3.) Return to main menu.\n");
    printf("==============================================\n");
    printf("> ");
    
    clearUserInput();
    setUserInput();
    int selectedChoice = atoi(getUserInput());

    switch(selectedChoice){
        case 1:
            changeIndex(userIndex);
            break;
        case 2:
            removeItem(userIndex);
            break;
        case 3:
            //pressEnterOther();
            break;
        default:
            printf("I'm sorry that value was not allowed. Try again");
            pressEnter();
            break;
    }
}