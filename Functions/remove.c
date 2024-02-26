#include "../Main Files/m_ClosetIQ.h"




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