#ifndef _MAIN_H_
#define _MAIN_H_
#define MAX_USER_ENTERABLE_SIZE 256
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
Defining function definitions to be used throughout the program
*/
int main();

/*
Viewing Functions
*/

void viewCloset();

/*
File I/O Functions
*/
void clearStdin();
int getLatestIndex();
void pressEnter();
char returnSavePath(int number);
char *getUserHomeDir();
void createDirectory(const char *path);
void userMenu();
void modifyCloset();
void pressEnter();
void removeItem(int targetIndex);
void userRemoveIndex();
void modifyClosetIndex(int userIndex);
void userSpecifyChangedIndex();
void pressEnterOther();
bool getOperatingSystem();
void addClothesToCloset();
void confirmAddToCloset(char nameOfTypeOfClothing[100], char nameOfColorOfClothing[100], int quantityOfClothing);
void removeCloset();