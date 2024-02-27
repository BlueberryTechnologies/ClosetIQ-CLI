#include "../Main Files/m_ClosetIQ.h"

/*
Functions
*/

void changeIndex(){
    clearUserInput();
    printf("Which index would you like to move?\n> ");
    int selectedIndex = atoi(getUserInput());
    printf("Which index would you like to replace?\n> ");
    clearUserInput();
    int replacedIndex = atoi(getUserInput());
}

/*
Implement setters and getters
*/