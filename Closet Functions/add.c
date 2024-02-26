#include "../Main Files/m_ClosetIQ.h"




/*
Variables
*/
char *userInput;
char *clothingType;
char *clothingColor;
int clothingQuantity;

/*
Main
*/

void addClothesToCloset(){
    getchar(); // Clear buffer

    char *currentClothesType = getClothingType();
    char *currentClothesColor = getClothingColor();
    int currentClothesQuantity = getClothingQuantity();

    // Checks if any values are NULL or 0.
    if (currentClothesType[0] == '\0' || currentClothesColor[0] == '\0' || currentClothesQuantity == 0)
    {
        printf("One or more values are NULL or 0, please try again!\n");
        addClothesToCloset();
    }
    confirmAddToCloset(currentClothesType, currentClothesColor, currentClothesQuantity);
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
        modifyClosetMenu();
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
Setters and Getters
*/




// Clothing Type

void setClothingType(){
    printf("What is the type of clothing?\n> ");
    clothingType = getUserInput();
}
char *getClothingType(){
    return clothingType;
}

// Clothing Color

void setClothingColor(){
    printf("What is the color of clothing?\n> ");
    clothingColor = getUserInput();
}
char *getClothingColor(){
    return clothingColor;
}

// Clothing Quantity

void setClothingQuantity(){
    printf("What is the quantity of clothing?\n> ");
    clothingQuantity = atoi(getUserInput());
}

int getClothingQuantity(){
    return clothingQuantity;
}