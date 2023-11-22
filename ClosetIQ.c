#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h> // For _mkdir on Windows
#else
#include <sys/stat.h> // For mkdir on Unix/Linux
#endif

/*
This will be a project to get the basic functionality of the program.
*/

char *returnSavePath();
void viewCloset();
char *getUserHomeDir();
void createDirectory(const char *path);
void userMenu();
void modifyCloset();

void addClothesToCloset();
void confirmAddToCloset(char nameOfTypeOfClothing[100], char nameOfColorOfClothing[100], int quantityOfClothing);

int main()
{
    char *path = returnSavePath();
    userMenu();
}

void userMenu()
{
    printf("==============================================\n");
    printf("%39s\n","ClosetIQ (Command Line Version!)");
    printf("%38s\n\n","Made by Blueberry Technologies");
    printf("1.) View the current closet.\n");
    printf("2.) Modify the current closet.\n");
    printf("3.) Choose an outfit (Coming Soon!)\n");
    printf("4.) Delete the current closet. (Coming Soon!)\n");
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
        printf("Coming soon!\n");
        break;
    case 4:
        printf("Coming soon!\n");
        break;
    default:
        printf("That choice was not allowed.\n");
        userMenu();
        break;
    }
}

void viewCloset()
/*
Shows the user's closet and current formatting.
*/
{
    char *path = returnSavePath();

    if (path == NULL){
        fprintf(stderr, "The path was not found.\n");
        return;
    }
    printf("The path is: %s\n", path);
    FILE *file = fopen(path, "r");

    if (file == NULL){
        fprintf(stderr, "Could not open the closet.\n");
        return;
    }
    char typeOfClothes[100];
    char colorOfClothes[100];
    int quantity;

    printf("==================================================\n");
    printf("%-20s %-20s %s\n", "Type of Clothes", "Color of Clothes", "Quantity");
    printf("==================================================\n");
    while (fscanf(file, "%99s %99s %d", typeOfClothes, colorOfClothes, &quantity) == 3){
        printf("%-20s %-20s %d\n", typeOfClothes, colorOfClothes, quantity);
    }

    fclose(file);
    free(path);
}

void modifyCloset()
/*
Allows the user to modify their closet. Add, remove, and change operations for the items within.
*/
{   
    int userModifyInput;
    printf("==============================================\n");
    printf("%30s\n\n", "Modify Closet.");
    printf("What would you like to do?\n");
    printf("1.) Add items from the closet.\n");
    printf("2.) Remove items from the closet.\n");
    printf("3.) Change existing items in the closet.\n");
    printf("4.) Return to the menu.\n");
    printf("==============================================\n");
    printf("> ");
    scanf("%d", &userModifyInput);

    switch(userModifyInput)
    {
        case 1:
        {
            addClothesToCloset();
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
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

void addClothesToCloset()
{
    char nameOfTypeOfClothing[100];
    printf("What is the type of clothing?\n");
    printf("> ");
    scanf("%99s", nameOfTypeOfClothing);

    char nameOfColorOfClothing[100];
    printf("\nWhat is the name of the color of the %ss?\n", nameOfTypeOfClothing);
    printf("> ");
    scanf("%99s", nameOfColorOfClothing);

    int quantityOfClothing;
    printf("\nHow many %s %ss do you have?\n", nameOfColorOfClothing, nameOfTypeOfClothing);
    printf("> ");
    scanf("%d", &quantityOfClothing);
    confirmAddToCloset(nameOfTypeOfClothing, nameOfColorOfClothing, quantityOfClothing);
}

void confirmAddToCloset(char nameOfTypeOfClothing[100], char nameOfColorOfClothing[100], int quantityOfClothing){
    char userConfirmation;
    printf("==============================================\n");
    printf("Type: %s\nColor: %s\nQuantity: %d\n\n", nameOfTypeOfClothing, nameOfColorOfClothing, quantityOfClothing);
    printf("Are these correct? (Y/N)\n");
    printf("> ");
    scanf(" %c", &userConfirmation);
    if (userConfirmation == 'Y'){
        printf("The values are being written to the closet.\n");
        /*
        Write values to closet here.
        */
        modifyCloset();
    }else if (userConfirmation == 'N'){
        printf("Please try again.\n");
        addClothesToCloset();
    }else{
        printf("That value was not recognized\n");
        confirmAddToCloset(nameOfTypeOfClothing, nameOfColorOfClothing, quantityOfClothing);
    }
    printf("==============================================\n");
}

void createDirectory(const char *path)
{
#ifdef _WIN32
    _mkdir(path);
#else
    mkdir(path, 0755);
#endif
}

char *returnSavePath() {
    FILE *closetData;
    char *homeDir = getUserHomeDir();
    if (homeDir == NULL) {
        fprintf(stderr, "Failed to get the user home directory.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate enough space for the new path
    char *dirPath = malloc(strlen(homeDir) + strlen("/ClosetIQ-CLI") + 1);
    if (dirPath == NULL) {
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
    if (filePath == NULL) {
        fprintf(stderr, "Memory allocation failed for file path.\n");
        free(homeDir);
        exit(EXIT_FAILURE);
    }
    strcat(filePath, "/closetIQData.txt");

    // Attempt to open the file for reading
    closetData = fopen(filePath, "r");
    if (closetData == NULL) {
        printf("The file was not found, creating a new file...\n");
        closetData = fopen(filePath, "w");
        if (closetData == NULL) {
            fprintf(stderr, "Failed to create the file at: %s\n", filePath);
            free(filePath);
            free(homeDir);
            exit(EXIT_FAILURE);
        } else {
            printf("The file was created at: %s\n", filePath);
        }
    }

    // Close the file if it was successfully opened or created
    if (closetData != NULL) {
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
