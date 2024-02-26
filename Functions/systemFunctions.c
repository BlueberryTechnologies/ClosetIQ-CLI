#include "../Main Files/m_ClosetIQ.h"
/*
Functions
*/


/*
Global Variables
*/
int globalIndex;
bool windows;
char *userInput;

/*
Setters and Getters
*/

bool getOperatingSystem(){

    if (windows){
        return true;
    }else{
        return false;
    }

}
void setOperatingSystem(bool boolean){
    if (boolean){
        windows = true;
    }else{
        windows = false;
    }
}

void setGlobalIndex(int index){
    index = globalIndex;
}
int getGlobalIndex(){
    return globalIndex;
}

void setUserInput(){
    char *inputFromUser = malloc(MAX_USER_ENTERABLE_SIZE);
    if (fgets(inputFromUser, 255, stdin))
    {
        inputFromUser[strcspn(inputFromUser, "\n")] = 0;
    }
    userInput = inputFromUser;
}
char *getUserInput(){
    return userInput;
}

int getLatestIndex(){ // This returns the index from the file
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

/*
System Functions
*/

void createDirectory(const char *path){
    #ifdef _WIN32
        _mkdir(path);
    #else
        mkdir(path, 0755);
    #endif
}
void pressEnter(){
    printf("Press the ENTER key to continue back to the menu:");
    int userProceed = getc(stdin);
    getchar();
    userMenu();
}
void pressEnterOther(){
    printf("Press the ENTER key to continue back to the menu:");
    int userProceed = getc(stdin);
    userMenu();
}
char *returnSavePath(int modifier)
{
    FILE *closetData;
    char *homeDir = getUserHomeDir();

    char *slash;

    if (getOperatingSystem() == true){
        slash = "\\";
    }else{
        slash = "/";
    }
    

    if (homeDir == NULL)
    {
        fprintf(stderr, "Failed to get the user home directory.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate enough space for the new path
    char *dirPath = malloc(strlen(homeDir) + strlen(slash) + strlen("ClosetIQ-CLI") + 1);
    if (dirPath == NULL)
    {
        fprintf(stderr, "Memory allocation failed for directory path.\n");
        free(homeDir);
        exit(EXIT_FAILURE);
    }
    strcpy(dirPath, homeDir);
    strcat(dirPath, slash);
    strcat(dirPath, "ClosetIQ-CLI");

    // Create the directory
    createDirectory(dirPath);

    // Append the filename to the directory path
    char *filePath = realloc(dirPath, strlen(dirPath) + strlen(slash) + strlen("closetIQData.txt") + 1);
    if (filePath == NULL)
    {
        fprintf(stderr, "Memory allocation failed for file path.\n");
        free(homeDir);
        exit(EXIT_FAILURE);
    }
    if (modifier == 0){
        strcat(filePath, slash);
        strcat(filePath, "closetIQData.txt");
    }else if(modifier == 1){
        strcat(filePath, slash);
        strcat(filePath, "closetIQDataTemp.txt");
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
    setOperatingSystem(true);
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
    setOperatingSystem(false);
    homeDir = getenv("HOME");

#endif

    if (homeDir == NULL)
    {
        printf("Cannot find the home directory.\n");
        exit(EXIT_FAILURE);
    }

    return strdup(homeDir);
}
