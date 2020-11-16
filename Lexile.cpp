/*AUTHOR: Brian Altamirano, Omar Mann*/
/*CPSC-323, Professor Le*/
/*Completed 9/18/2020*/


#include "Lexile.h"


int Lexile()
{
	/*Initializations for the program to work properly*/
	int indexNum = 0;
	char givenChar, currentCase = 'A'; // currentCase: Starting point of the FSM
	char charArray[BUFSIZ]; // General Buffer to store character arrays
	bool isString = false, isComment = false, isNumber = false; // Used to differentiate, useful.

	/*Banks for the keywords, Operators, and Symbols to differentiate*/
	const char* keywordBank[] = { "int", "float", "bool", "true", "false", "if", "else", "then", "endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output", "and", "or", "not" }; // ISSUE: sizeof() gives wrong amount, returns 80 when it should return 20.
	char symbolBank[12] = { '\'', '(', ')', '{', '}', '[', ']', ',' , ':' , ';', ' ' };
	char operatorBank[8] = { '>', '+', '-', '=', '/', '*' , '<', '%' };

	/* This is a C style array memory allocation and clear. We can change it to C++ later.*/
	memset(charArray, 0, sizeof(BUFSIZ));

	/* C style Open input File*/
	FILE* fin = fopen("input.txt", "r");
	/* C style Open output File*/
	FILE* fout = fopen("Lexoutput.txt", "w");

	while ((givenChar = fgetc(fin))!= EOF) //While statement to read the input file 1 char at a time
	{
     /* file input loop                  */

		/*FSM*/

	SWITCHCASE: // Goto to prevent moving on to the next char and changing Switch Case.


		switch (currentCase) {
		case 'A':
			/* This case determines what the given character from the stream is what. Then we go to the case necessary for processing*/
			if (isSeperator(givenChar, symbolBank, sizeof(symbolBank)))
			{
				currentCase = 'B';
				if (isString)  // This condition and body is reused to check if the current Char is a continuation or the end of a char or number string. Once we get to a symbol/operation, we assume the end of a string.
				{
					charArray[indexNum] = '\0'; // Necessary to signify end of array
					printString(charArray, keywordBank, 20, isNumber, fout); // Prints string and passes the character Array, the Bank for keywords, the amount in the bank, if it is a number, and the FILE output stream 
					memset(charArray, 0, sizeof(BUFSIZ)); // clear
					indexNum = 0; // once clear, we go to the beginning of the array
					isString = false; // Signifies we are not recording an array
				}

				goto SWITCHCASE;
			}
			else if (isOperator(givenChar, operatorBank, sizeof(operatorBank)))
			{
				currentCase = 'C';
				if (isString)
				{
					charArray[indexNum] = '\0';
					printString(charArray, keywordBank, 20, isNumber, fout);
					memset(charArray, 0, sizeof(BUFSIZ));
					indexNum = 0;
					isString = false;
				}
				goto SWITCHCASE;
			}
			else if (isdigit(givenChar) || givenChar == '.')
			{
				currentCase = 'D';
				if (!isString) { isNumber = true; } //If it's not a string, its a number string.

				goto SWITCHCASE;
			}
			else if (isalpha(givenChar) || givenChar == '$') // $ is counted as a part of an identifier
			{
				currentCase = 'E';
				goto SWITCHCASE;
			}
			else if (givenChar == '!')
			{
				currentCase = 'F';
				if (isString)
				{
					charArray[indexNum] = '\0';
					printString(charArray, keywordBank, 20, isNumber,fout);
					memset(charArray, 0, sizeof(BUFSIZ));
					indexNum = 0;
					isString = false;
				}
				goto SWITCHCASE;
			}

			break;
		case 'B':
			if (givenChar == ' ') // If its a space, print SEPERATOR = sp
			{
			//fprintf(fout,"\nSEPERATOR = sp");
			currentCase = 'A';
			}
			else {
				fprintf(fout,"\nSEPERATOR = %c", givenChar); //Otherwise print whatever seperator it is.
				currentCase = 'A';
			}
			break;

		case 'C':
			fprintf(fout,"\nOPERATOR = %c", givenChar); // Print the Operator
			currentCase = 'A';
			break;

		case 'D':
			if (!isString) // If it is not currently part of a string and its a character, then it is the beginning of one
			{
				charArray[indexNum++] = givenChar;
				currentCase = 'A';
				isString = true;
				break;
			}
			else
			{
				charArray[indexNum++] = givenChar; // Otherwise, we add to the number array (charArray)
				currentCase = 'A';
			}
			break;




		case 'E':
			if (!isString)
			{
				charArray[indexNum++] = givenChar;// If it is not currently part of a string and its a character, then it is the beginning of one
				currentCase = 'A';
				isString = true;
				break;
			}
			else
			{
				charArray[indexNum++] = givenChar; // Otherwise, we add to the number array (charArray)
				currentCase = 'A';
			}

			break;





		case 'F':
			if (!isComment) // If this is the first !, then it is the beginning of the comment, ignore any following inputs.
			{
				isComment = true;
				currentCase = 'F';
			}
			else if (givenChar == '!' && isComment) // If it is currently a comment and we get an Exclamation point, start recognizing inputs
			{
				currentCase = 'A';
			}
			else
			{
				break;
			}
			break;

		}


	}

	fclose(fin); // Close input stream
	fclose(fout); // close output stream
	return 0;
}



bool isSeperator(char x, char symbolBank[], int symbolBankSize)
{
	return CharBankCmp(x, symbolBank, symbolBankSize); // checks if it is a valid seperator
}


bool isOperator(char x, char operatorBank[], int symbolBankSize)
{
	return CharBankCmp(x, operatorBank, symbolBankSize); //checks if it is a valid operator
}

/* How we output the strings*/
void printString(char* givenstringArray, const char* keywordBank[], int keywordBankSize, bool &isNumber, FILE* fout) 
{
	if (isNumber) //If it is a number, print out the current array as it is until \0. 
	{
		fprintf(fout,"\nNUMBER = ");
		for (int i = 0; givenstringArray[i] != '\0'; ++i)
		{
			fprintf(fout,"%c", givenstringArray[i]);
		}
		isNumber = false; // Once that is done the charArray is no longer a number
	}
	else if (KeywordBankCmp(givenstringArray, keywordBank, keywordBankSize)) // IF its not a number, check if the Character array is a keyword
	{
		fprintf(fout,"\nKEYWORD = ");

		for (int i = 0; givenstringArray[i] != '\0' ; ++i)
		{
			fprintf(fout,"%c", givenstringArray[i]);
		}
	}
	else // Otherwise print it out as an identifier.
	{
		fprintf(fout,"\nIDENTIFIER = ");

		for (int i = 0; givenstringArray[i] != '\0'; ++i)
		{
			fprintf(fout,"%c", givenstringArray[i]);
		}
	}

}

bool CharBankCmp(char x, char bank[], int bankSize) // Compare char bank with the given char to check if it is a keyword or valid operator
{
	for (int i = 0; i != bankSize; ++i)
	{
		if (x == bank[i])
		{
			return true;
		}

	}
	return false;
}

bool KeywordBankCmp(char* givenString, const char* givenStringBank[], int givenStringBankSize) //Compare to find out if the charArray is a keyword.
{
	for (int i = 0; i != givenStringBankSize; ++i)
	{
		if (strcmp(givenString, givenStringBank[i]) == 0) {
			return true;
		}
	}
	return false;
}
