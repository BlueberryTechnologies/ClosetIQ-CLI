#include <stdio.h>
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
void closetIQFileManager();
void viewCloset();
char* getUserHomeDir();
void createDirectory(const char* path);

void userMenu();


int main(){
    closetIQFileManager(); // This is the file manager for the program. This will initialize the current files for the usage in the program.
    userMenu();
}

void userMenu(){
    printf("=========================\nClosetIQ (Command Line Version!)\nMade by Blueberry Technologies\n\nPlease review the menu.\n\n1.) View the current closet.\n2.) Modify the current closet.\n3.) Choose an outfit\n4.) Delete the current closet and define a new one.\n> ");
    int userChoice;
    scanf("%d", &userChoice);

    switch(userChoice){
        case 1:
            viewCloset();
            break;
        default:
            printf("That choice was not allowed.\n");
    }
}

void viewCloset(){
    printf("Here is the current closet:");
}

void createDirectory(const char* path){
    #ifdef _WIN32
    _mkdir(path);
    #else
    mkdir(path, 0755);
    #endif

}

void closetIQFileManager(){
    FILE* closetData; // Make a pointer to point to the contents of the file.
    char* homeDir = getUserHomeDir();
    // Allocate enough space for the new path
    char* dirPath = malloc(strlen(homeDir) + strlen("/ClosetIQ-CLI") + 1);
    if (dirPath == NULL) {
        printf("Memory allocation failed.\n");
        free(homeDir); // Don't forget to free homeDir if it was dynamically allocated
        return;
    }
    strcpy(dirPath, homeDir);
    strcat(dirPath, "/ClosetIQ-CLI");

    // Create the directory
    createDirectory(dirPath);

    // Append the filename to the directory path
    char* filePath = realloc(dirPath, strlen(dirPath) + strlen("/closetIQData.txt") + 1);
    if (filePath == NULL) {
        printf("Memory allocation failed.\n");
        free(dirPath);
        free(homeDir);
        return;
    }
    strcat(filePath, "/closetIQData.txt");

    // Attempt to open the file for reading
    closetData = fopen(filePath, "r");

    if (closetData == NULL) {
        // The file wasn't found, try to create it
        printf("The file was not found.\n");
        closetData = fopen(filePath, "w");
        if (closetData != NULL) {
            printf("The file was created at: %s\n", filePath);
        } else {
            perror("Error");
        }
    }

    // Close the file if it was successfully opened or created
    if (closetData != NULL) {
        fclose(closetData);
    }

    // Free the allocated memory
    free(filePath); // Note: filePath and dirPath point to the same block of memory after realloc
    free(homeDir);
}

char* getUserHomeDir(){
    char* homeDir;

    #ifdef _WIN32
        homeDir = getenv("USERPROFILE");
        if(homeDir == NULL) {
            homeDir = getenv("HOMEDRIVE");
            if(homeDir != NULL) {
                char* homePath = getenv("HOMEPATH");
                if(homePath != NULL) {
                    char* fullPath = malloc(strlen(homeDir) + strlen(homePath) + 1);
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

    if (homeDir == NULL){
        printf("Cannot find the home directory.\n");
        exit(EXIT_FAILURE);
    }

    return strdup(homeDir);
}