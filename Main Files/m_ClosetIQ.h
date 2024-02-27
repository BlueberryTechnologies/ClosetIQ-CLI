#ifndef _MAIN_H_
#define _MAIN_H_
#define MAX_USER_ENTERABLE_SIZE 256 // This is the max number of characters a user can enter into any input.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#include <direct.h> // For _mkdir on Windows
#else
#include <sys/stat.h> // For mkdir on Unix/Linux
#endif
#endif

/*
Global Functions
*/
void setClothingType();
char *getClothingType();
void setClothingColor();
char *getClothingColor();
void setClothingQuantity();
int getClothingQuantity();
void confirmAddToCloset(char nameOfTypeOfClothing[100], char nameOfColorOfClothing[100], int quantityOfClothing);
void addClothesToCloset();
////////////////
void removeCloset();
void removeItem(int targetIndex);
////////////////
void setUserInput();
char *getUserInput();
void clearUserInput();
void setGlobalIndex(int index);
int getGlobalIndex();
int getLatestIndex();
void pressEnter();
void pressEnterOther();
void clearBuffer();
bool getOperatingSystem();
void setOperatingSystem(bool boolean);
char *returnSavePath(int modifier);
char *getUserHomeDir();
////////////////
void modifyIndex();
void modifyIndexMenu(int userIndex);
////////////////
int main();
void userMenu();
void modifyClosetMenu();
void viewCloset();
////////////////
void changeIndex();