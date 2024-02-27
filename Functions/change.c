#include "../Main Files/m_ClosetIQ.h"

int indexInsideFile;
char *firstNameOfClothing;
char *firstNameOfColorOfClothing;
int firstQuantity;
char *secondNameOfClothing;
char *secondNameOfColorOfClothing;
int secondQuantity;
int count = 1;
bool thingsSwappedOne = false;
bool thingsSwappedTwo = false;


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

void setFirstName(char *firstName){
    char *firstNameTemp = malloc(MAX_USER_ENTERABLE_SIZE);
    firstNameTemp = firstName;
    firstNameOfClothing = firstNameTemp;
}

char *getFirstName(){
    return firstNameOfClothing;
}

void setSecondName(char *secondName){
    char *secondNameTemp = malloc(MAX_USER_ENTERABLE_SIZE);
    secondNameTemp = secondName;
    secondNameOfClothing = secondNameTemp;
}

char *getSecondName(){
    return secondNameOfClothing;
}

void setFirstColor(char *firstColor){
    char *firstColorTemp = malloc(MAX_USER_ENTERABLE_SIZE);
    firstColorTemp = firstColor;
    firstNameOfColorOfClothing = firstColorTemp;
}

char *getFirstColor(){
    return firstNameOfColorOfClothing;
}

void setSecondColor(char *secondColor){
    char *secondColorTemp = malloc(MAX_USER_ENTERABLE_SIZE);
    secondColorTemp = secondColor;
    secondNameOfColorOfClothing = secondColorTemp;
}

char *getSecondColor(){
    return secondNameOfColorOfClothing;
}

void setFirstQuantity(int firstQuant){
    firstQuantity = firstQuant;
}

int getFirstQuantity(){
    return firstQuantity;
}

void setSecondQuantity(int secondQuant){
    secondQuantity = secondQuant;
}

int getSecondQuantity(){
    return secondQuantity;
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
    

    while (fscanf(inputFile, "%d %s %s %d", &indexInsideFile, currNameOfClothing, currNameOfColorOfClothing, &currQuantity) == 4) {
        if (indexInsideFile != indexOne && indexInsideFile != indexTwo) {
            printf("Index: %d does not equal %d or %d\n", indexInsideFile, indexOne, indexTwo);
        }
        if(indexInsideFile == indexOne){
            setFirstName(currNameOfClothing);
            setFirstColor(currNameOfColorOfClothing);
            setFirstQuantity(currQuantity);
            printf("First Index Before Swap (%d): %s, %s, %d\n", indexInsideFile, getFirstName(), getFirstColor(), getFirstQuantity());
        }
        if(indexInsideFile == indexTwo){
            setSecondName(currNameOfClothing);
            setSecondColor(currNameOfColorOfClothing);
            setSecondQuantity(currQuantity);
            printf("Second Index Before Swap (%d): %s, %s, %d\n\n", indexInsideFile, getSecondName(), getSecondColor(), getSecondQuantity());
        }
    }

    fclose(inputFile);

    FILE *inputFileTwo = fopen(returnSavePath(0), "r");
    if (inputFileTwo == NULL) {
        fprintf(stderr, "Could not open the file.\n");
        return;
    }

    while (fscanf(inputFileTwo, "%d %s %s %d", &indexInsideFile, currNameOfClothing, currNameOfColorOfClothing, &currQuantity) == 4) {
        if (indexInsideFile != indexOne && indexInsideFile != indexTwo) {
            fprintf(outputFile, "%d %s %s %d\n", count, currNameOfClothing, currNameOfColorOfClothing, currQuantity);
            count++;
            printf("NOT ALLOWED\n");
        }
        if(indexInsideFile == indexOne){ // If the index is the first value
            printf("Second Values -> First Index: %s, %s, %d\n", getFirstName(), getFirstColor(), getFirstQuantity());
            fprintf(outputFile, "%d %s %s %d\n", indexOne, getFirstName(), getFirstColor(), getFirstQuantity());
            thingsSwappedOne = true;
            count++;
            printf("First Index After Swap (%d) is: %s, %s, %d\n", indexInsideFile, getSecondName(), getSecondColor(), getSecondQuantity());
        }
        if(indexInsideFile == indexTwo){ // If the index is the second value
            printf("First Values -> Second Index: %s, %s, %d\n", getSecondName(), getSecondColor(), getSecondQuantity());
            fprintf(outputFile, "%d %s %s %d\n", indexTwo, getSecondName(), getSecondColor(), getSecondQuantity());
            thingsSwappedTwo = true;
            count++;
            printf("Second Index After Swap (%d) is: %s, %s, %d\n", indexInsideFile, getFirstName(), getFirstColor(), getFirstQuantity());
        }
    }

    


    if (thingsSwappedOne && thingsSwappedTwo){
        fclose(outputFile);
        fclose(inputFileTwo);
        //remove(path);
        //rename(returnSavePath(1), path);
        printf("The value at index %d and %d was swapped successfully!\n", indexOne, indexTwo);
    }else{
        printf("There are no values to swap at that index. Try again.\n");
        pressEnterOther();
    }
}

/*
Implement setters and getters
*/