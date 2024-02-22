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

#define MAX_USER_ENTERABLE_SIZE 256

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

int globalIndex;


void clearStdin();
int getLatestIndex();
void pressEnter();
char *returnSavePath(int number);
void viewCloset();
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


void addClothesToCloset();
void confirmAddToCloset(char nameOfTypeOfClothing[100], char nameOfColorOfClothing[100], int quantityOfClothing);

void removeCloset();

int main()
{
    char *path = returnSavePath(0);
    userMenu();
}

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
        modifyCloset();
        break;
    case 3:
        /*
        printf("Coming soon!\n");
        pressEnter();
        */
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

/*

Setters and Getters

*/

void setIndex(int index){
    index = globalIndex;
}

int getIndex(){
    return globalIndex;
}


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

void modifyCloset()
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
        userSpecifyChangedIndex();
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
        modifyCloset();
        break;
    }
    }
}

/*

ADD TO CLOSET

*/

char* returnNameOfColor(){

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    char *nameOfColorOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    printf("What is the name of the color of the clothing?\n> ");
    
    if (fgets(nameOfColorOfClothing, 255, stdin))
    {
        nameOfColorOfClothing[strcspn(nameOfColorOfClothing, "\n")] = 0;
    }
    printf("Press ENTER to continue.");
    return nameOfColorOfClothing;
}

char* returnNameOfType(){

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    char *nameOfTypeOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    printf("What is the name of the clothing?\n> ");
    
    if (fgets(nameOfTypeOfClothing, 255, stdin))
    {
        nameOfTypeOfClothing[strcspn(nameOfTypeOfClothing, "\n")] = 0;
    }
    printf("Press ENTER to continue.");
    return nameOfTypeOfClothing;
}

char* returnQuantityOfClothing(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    char *quantityOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    printf("What is the quantity of the clothing?\n> ");
    
    if (fgets(quantityOfClothing, 255, stdin))
    {
        quantityOfClothing[strcspn(quantityOfClothing, "\n")] = 0;
    }
    return quantityOfClothing;
}

void addClothesToCloset()
{

    char *currentClothesType = returnNameOfType();
    char *currentClothesColor = returnNameOfColor();
    char *currentClothesQuantity = returnQuantityOfClothing();

    
    if (currentClothesType[0] == '\0' || currentClothesColor[0] == '\0' || currentClothesQuantity == 0)
    {
        printf("One or more values are NULL or 0, please try again!\n");
        addClothesToCloset();
    }
    

    printf("Color: %s\nType: %s\nQuantity: %s\n", currentClothesColor, currentClothesType, currentClothesQuantity);

    int currentClothesQuantityInt = atoi(currentClothesQuantity);
    
    confirmAddToCloset(currentClothesType, currentClothesColor, currentClothesQuantityInt);
    
}

void confirmAddToCloset(char nameOfTypeOfClothing[100], char nameOfColorOfClothing[100], int quantityOfClothing)
{
    char userConfirmation;
    printf("==============================================\n");
    printf("Type: %s\nColor: %s\nQuantity: %d\n\n", nameOfTypeOfClothing, nameOfColorOfClothing, quantityOfClothing);
    printf("Are these correct? (Y/N)\n");
    printf("> ");
    scanf(" %c", &userConfirmation);
    if (tolower(userConfirmation) == 'y')
    {
        int index = getLatestIndex() + 1;
        printf("The values are being written to the closet.\n");
        FILE *file = fopen(returnSavePath(0), "a");
        if (file)
        {
            fprintf(file, "%d %s   %s  %d\n", index, nameOfTypeOfClothing, nameOfColorOfClothing, quantityOfClothing);
            fclose(file);
        }
        printf("The values were successfully written to the closet.\n");
        modifyCloset();
    }
    else if (tolower(userConfirmation) == 'n')
    {
        printf("Please try again.\n");
        addClothesToCloset();
    }
    else
    {
        printf("That value was not recognized\n");
        confirmAddToCloset(nameOfTypeOfClothing, nameOfColorOfClothing, quantityOfClothing);
    }
    printf("==============================================\n");
}

/*

REMOVE CLOSET

*/

void removeCloset()
{
    FILE *file = fopen(returnSavePath(0), "w");
    fprintf(file, "");
    fclose(file);
    int fileContents = fgetc(file);

    if (fileContents == EOF)
    {
        printf("The closet was deleted successfully!\n");
        pressEnter();
    }
    else
    {
        printf("The contents were not deleted. :(\n");
        exit(EXIT_FAILURE);
    }
}



void userSpecifyChangedIndex(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    char *specifiedIndex = malloc(MAX_USER_ENTERABLE_SIZE);
    printf("What is the index you would like to modify?\n> ");
    
    if (fgets(specifiedIndex, 255, stdin))
    {
        specifiedIndex[strcspn(specifiedIndex, "\n")] = 0;
    }
    printf("Press ENTER to continue.");
    modifyClosetIndex(atoi(specifiedIndex));
}

void modifyClosetIndex(int userIndex){
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

void removeItem(int targetIndex){
    char *path = returnSavePath(0);

    if (path == NULL) {
        fprintf(stderr, "The path was not found.\n");
        return;
    }

    FILE *inputFile = fopen(returnSavePath(0), "r");

    if (inputFile == NULL) {
        fprintf(stderr, "Could not open the file.\n");
        return;
    }

    FILE *outputFile = fopen(returnSavePath(1), "w");  // Create a temporary file

    if (outputFile == NULL) {
        fprintf(stderr, "Could not create the temporary file.\n");
        fclose(inputFile);
        return;
    }

    
    int index;
    char nameOfClothing[100];
    char nameOfColorOfClothing[100];
    int quantity;
    int count = 1;
    bool thingsDeleted = false;

    while (fscanf(inputFile, "%d %s %s %d", &index, nameOfClothing, nameOfColorOfClothing, &quantity) == 4) {
        if (index != targetIndex) {
            fprintf(outputFile, "%d %s %s %d\n", count, nameOfClothing, nameOfColorOfClothing, quantity);
            count++;
        }
        else{
            thingsDeleted = true;
        }
    }

    if (thingsDeleted){
        fclose(outputFile);
        fclose(inputFile);
        remove(path);
        rename(returnSavePath(1), path);
        printf("The value at index %d was removed successfully!\n", targetIndex);
        pressEnterOther();
    }else{
        printf("There are no values at that index. Try again.\n");
        pressEnterOther();
    }
}

/*

FILE IO


*/

int getLatestIndex(){
    char *path = returnSavePath(0);

    if (path == NULL)
    {
        fprintf(stderr, "The path was not found.\n");
        return -1;
    }
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open the closet.\n");
        return -1;
    }

    int index;

    while (fscanf(file, "%d %*s %*s %*d", &index) != 1)
    {
        return 0;
    }

    while (fscanf(file, "%d %*s %*s %*d", &index) == 1)
    {
        printf("Index: %d\n", index);
        index = index;
    }

    

    printf("The index is: %d\n", index);
    
    return index;
}


void pressEnter(){
    printf("Press the ENTER key to continue back to the menu:");
    int userProceed = getc(stdin);
    clearStdin();
    userMenu();
}

void pressEnterOther(){
    printf("Press the ENTER key to continue back to the menu:");
    int userProceed = getc(stdin);
    userMenu();
}

void clearStdin()
{
    // keep reading 1 more char as long as the end of the stream, indicated by the newline char,
    // has NOT been reached
    while (true)
    {
        int c = getc(stdin);
        if (c == EOF || c == '\n')
        {
            break;
        }
    }
}


void createDirectory(const char *path)
{
#ifdef _WIN32
    _mkdir(path);
#else
    mkdir(path, 0755);
#endif
}

char *returnSavePath(int modifier)
{
    FILE *closetData;
    char *homeDir = getUserHomeDir();
    if (homeDir == NULL)
    {
        fprintf(stderr, "Failed to get the user home directory.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate enough space for the new path
    char *dirPath = malloc(strlen(homeDir) + strlen("/ClosetIQ-CLI") + 1);
    if (dirPath == NULL)
    {
        fprintf(stderr, "Memory allocation failed for directory path.\n");
        free(homeDir);
        exit(EXIT_FAILURE);
    }
    strcpy(dirPath, homeDir);
    strcat(dirPath, "/ClosetIQ-CLI");

    // Create the directory
    createDirectory(dirPath);

    // Append the filename to the directory path
    char *filePath = realloc(dirPath, strlen(dirPath) + strlen("/closetIQData.txt") + 1);
    if (filePath == NULL)
    {
        fprintf(stderr, "Memory allocation failed for file path.\n");
        free(homeDir);
        exit(EXIT_FAILURE);
    }
    if (modifier == 0){
        strcat(filePath, "/closetIQData.txt");
    }else if(modifier == 1){
        strcat(filePath, "/closetIQDataTemp.txt");
    }

    // Attempt to open the file for reading
    closetData = fopen(filePath, "r");
    if (closetData == NULL)
    {
        if (modifier == 0){
            printf("The file was not found, creating a new file...\n");
        }
        
        closetData = fopen(filePath, "w");
        if (closetData == NULL)
        {
            if (modifier == 0){
                fprintf(stderr, "Failed to create the file at: %s\n", filePath);
            }
            free(filePath);
            free(homeDir);
            exit(EXIT_FAILURE);
        }
        else
        {
            if (modifier == 0){
                printf("The file was created at: %s\n", filePath);
            }
            
        }
    }

    // Close the file if it was successfully opened or created
    if (closetData != NULL)
    {
        fclose(closetData);
    }

    free(homeDir); // Free homeDir after it's no longer needed

    // Return filePath which now contains the path to the file
    return filePath;
}
char *getUserHomeDir()
{
    char *homeDir;

#ifdef _WIN32
    homeDir = getenv("USERPROFILE");
    if (homeDir == NULL)
    {
        homeDir = getenv("HOMEDRIVE");
        if (homeDir != NULL)
        {
            char *homePath = getenv("HOMEPATH");
            if (homePath != NULL)
            {
                char *fullPath = malloc(strlen(homeDir) + strlen(homePath) + 1);
                strcpy(fullPath, homeDir);
                strcat(fullPath, homePath);
                return fullPath; // Caller must free this
            }
        }
    }
#else
    // On Unix-like systems, use HOME environment variable
    homeDir = getenv("HOME");

#endif

    if (homeDir == NULL)
    {
        printf("Cannot find the home directory.\n");
        exit(EXIT_FAILURE);
    }

    return strdup(homeDir);
}
