#include "../Main Files/m_ClosetIQ.h"

/*
Functions
*/

void changeIndex(int firstIndex){
    clearUserInput();
    printf("Which index would you like to swap index %d with?\n> ", firstIndex);
    setUserInput();
    int replacedIndex = atoi(getUserInput());
    swapIndexes(firstIndex, replacedIndex);

}

void swapIndexes(int indexOne, int indexTwo){
    printf("Index One: %d\nIndex Two: %d\n", indexOne, indexTwo);
    
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

    int indexInsideFile;
    char *firstNameOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    char *firstNameOfColorOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    int firstQuantity;
    char *secondNameOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    char *secondNameOfColorOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    int secondQuantity;
    char *currNameOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    char *currNameOfColorOfClothing = malloc(MAX_USER_ENTERABLE_SIZE);
    int currQuantity;
    int count = 1;
    bool thingsDeleted = false;

    while (fscanf(inputFile, "%d %s %s %d", &indexInsideFile, currNameOfClothing, currNameOfColorOfClothing, &currQuantity) == 4) {
        if (indexInsideFile != indexOne && indexInsideFile != indexTwo) {
            printf("Index: %d does not equal %d or %d\n", indexInsideFile, indexOne, indexTwo);
        }
        if(indexInsideFile == indexOne){
            firstNameOfClothing = currNameOfClothing;
            firstNameOfColorOfClothing = currNameOfColorOfClothing;
            firstQuantity = currQuantity;
            printf("Index One (%d) is: %s, %s, %d\n", indexInsideFile, firstNameOfClothing, firstNameOfColorOfClothing, firstQuantity);
        }
        if(indexInsideFile == indexTwo){
            secondNameOfClothing = currNameOfClothing;
            secondNameOfColorOfClothing = currNameOfColorOfClothing;
            secondQuantity = currQuantity;
            printf("Index Two (%d) is: %s, %s, %d\n", indexInsideFile, secondNameOfClothing, secondNameOfColorOfClothing, secondQuantity);
        }
    }
    printf("The First Index Values are: %s, %s, %d\nThe Second Index Values are: %s, %s, %d\n", firstNameOfClothing, firstNameOfColorOfClothing, firstQuantity, secondNameOfClothing, secondNameOfColorOfClothing, secondQuantity);
}

/*
Implement setters and getters
*/