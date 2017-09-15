// Jonathan Grant
// CS231
// Encryptions
// This program will allow the user to enter 10 lines of 50 characters,
// and will encrypt the lines based off of their ASCII table value by
// using a specified offset value.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// This two-dimensional array will contain the
// 10 lines of 50 characters that the user inputs.
static const int ARRAYLENGTH = 50;
char line[10][50];
char encryptedLine[10][50];
char decryptedLine[10][50];

void Instructions(){

	printf("\nEncrypt a text!\n\n");
	printf("You are allowed to enter 10 lines of 50 characters.\n");
	printf("If you wish to enter less than 10 lines, just hit enter\n");
	printf("on a blank line and the program will start encrypting.\n\n");
}

int InputOffset(){

	char offsetArray[10];
	int offsetInt;

	printf("Enter offset value for encryption: ");

	fgets(offsetArray, 10, stdin);
	offsetInt = atoi(offsetArray);

	printf("\nOffset value entered: %d\n", offsetInt);

	return offsetInt;
}

int InputText(){

	int lineCount = 0;

	printf("\n\nEnter up to 10 lines of 50 characters each below:\n\n");

	// While the user is still under ten lines and doesn't enter
	// a blank line, allow them to keep entering lines.
	do {
		printf("%d. ", lineCount + 1);
		fgets(line[lineCount], ARRAYLENGTH, stdin);
		lineCount++;

	} while((line[lineCount-1][0] != '\n') && (lineCount < 10));

	// Get rid of the new line character at the end of each line
	for(int i = 0; i < lineCount; i++){
		line[i][strlen(line[i]) - 1] = '\0';

		// Using the convenience of the for loop with i
		// iterating, copy the original text into the
		// encrypted array.
		for (int j = 0; j < strlen(line[i]); j++)
			encryptedLine[i][j] = line[i][j];
	}

	return lineCount;
}

void PrintText(char charArray[][50], int lineCount){

	printf("\n\n");

	for (int i=0; i< lineCount; i++){
		printf("%d. ", i + 1);
		printf("%s", charArray[i]);
		printf("\n");
	}
}

void ChangeCase(char charArray[][50], int i, int j){

	// Note that this function assumes that the character
	// being passed into is is alphabetic.

	// Change upper case letters to lower case
	if (isupper(charArray[i][j])){
		charArray[i][j] += 32;
	}

	// Change lower case letters to upper case
	else{
		charArray[i][j] -= 32;
	}
}

void EncryptLine(int numLines, int offset){

	int tempValue;

	// Simplify the offset value.
	// ex. If it is 95, it will be simplified to 0.
	offset = offset % 95;

	for (int i = 0; i < numLines; i++){

		for (int j = 0; j < strlen(line[i]); j++){

			// Change the case of the character if
			// it is an alphabetic letter
			if (isalpha(line[i][j]))
				ChangeCase(encryptedLine, i, j);

			// If the character is within the range of
			// encryptable characters, the offset
			// value is added.
			if (32 <= encryptedLine[i][j] <= 126){

				// Add the offset value to an integer instead
				// of the encryptedLine character to be safe.
				tempValue = encryptedLine[i][j] + offset;

				while (tempValue > 126)
					tempValue -= 95;

				while (tempValue < 32)
					tempValue += 95;

				// Once the temporary integer is back within
				// the range of encryptable ASCII values,
				// assign the encrypted character to it.
				encryptedLine[i][j] = tempValue;
			}

			// Out of convenience again in the nested for loops,
			// this is a good spot to copy the encrypted array
			// into the decrypted array.
			decryptedLine[i][j] = encryptedLine[i][j];
		}
	}
}

void DecryptLine(int numLines, int offset){

        int tempValue;

        offset = offset % 95;

        for (int i = 0; i < numLines; i++){

                for (int j = 0; j < strlen(encryptedLine[i]); j++){

                        if (32 <= encryptedLine[i][j] <= 126){

                                tempValue = encryptedLine[i][j] - offset;

                                while (tempValue > 126)
                                        tempValue -= 95;

                                while (tempValue < 32)
                                        tempValue += 95;

                                decryptedLine[i][j] = tempValue;
                        }

                        if (isalpha(decryptedLine[i][j]))
                                ChangeCase(decryptedLine, i, j);
                }
        }
}

int CompareLines(int numberOfLines){

	int same = -1;
	int lineCount = 0;
	int charCount = 0;

	while (same && lineCount < numberOfLines) {
		while (same && charCount < strlen(line[lineCount])){
			same = (line[lineCount][charCount] == decryptedLine[lineCount][charCount]);
			charCount++;
		}
		lineCount++;
	}

	return same;
}

void PrintResult(int result){

	if (result)
		printf("\nThe line has successfully been decrypted.\n");
	else
		printf("\nThe line has not been successfully decrypted.\n");

}

void main(){

	int numberOfLines;
	int offset;
	int result;

	Instructions();

	offset = InputOffset();

	numberOfLines = InputText();

	printf("\nWhat you input:");
	PrintText(line, numberOfLines);

	EncryptLine(numberOfLines, offset);

	printf("\nEncrypted line:");
	PrintText(encryptedLine, numberOfLines);

	DecryptLine(numberOfLines, offset);

	printf("\nDecrypted line:");
	PrintText(decryptedLine, numberOfLines);

	result = CompareLines(numberOfLines);

	PrintResult(result);
}
