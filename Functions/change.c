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

    
    char *currNameOfClothing;
    char *currNameOfColorOfClothing;
    int currQuantity;
    bool thingsSwappedOne = false;
    bool thingsSwappedTwo = false;
    int indexInsideFile;
    
    int oldCount = 0;
    while (fscanf(inputFile, "%d %s %s %d", &indexInsideFile, currNameOfClothing, currNameOfColorOfClothing, &currQuantity) == 4) {
        if (indexInsideFile != indexOne && indexInsideFile != indexTwo) {
            printf("Index: %d does not equal %d or %d\n", indexInsideFile, indexOne, indexTwo);
        }
        if (indexInsideFile == indexOne){
            fprintf(outputFile, "%d %s %s %d\n", indexTwo, currNameOfClothing, currNameOfColorOfClothing, currQuantity);
            thingsSwappedOne = true;
        }
        if (indexInsideFile == indexTwo){
            fprintf(outputFile, "%d %s %s %d\n", indexOne, currNameOfClothing, currNameOfColorOfClothing, currQuantity);
            thingsSwappedTwo = true;
        }
        oldCount++;
        printf("Old Count: %d\n", oldCount);
    }
    bool finished = false;
    int count = 0;
    while(count != oldCount){
        while (fscanf(outputFile, "%d %s %s %d", &indexInsideFile, currNameOfClothing, currNameOfColorOfClothing, &currQuantity) == 4) {
            if (count == indexInsideFile){
                fprintf(inputFile, "%d %s %s %d", count, currNameOfClothing, currNameOfColorOfClothing, currQuantity);
            }
        }
        count++;
        printf("New Count: %d\n", count);
    }
    if (thingsSwappedOne && thingsSwappedTwo){
        fclose(outputFile);
        fclose(inputFile);
        remove(path);
        rename(returnSavePath(1), path);
        printf("\n\nThe value at index %d and %d was swapped successfully!\n", indexOne, indexTwo);
    }else{
        printf("\n\nThere are no values to swap at that index. Try again.\n");
        pressEnterOther();
    }
}

/*
Implement setters and getters
*/