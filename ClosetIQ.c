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

int main()
{
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

void modifyCloset(){

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
