#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "LContainer.h"
#include "Parser.h"

//First Mission: Decode each line of the output from the lexile analyzer into classes of Leximes and Tokens -Done
	//Second Mission: Be able to traverse the 'class array' of Tokens and Lexemes -Done
	//Third Mission: Implement the funtions aka Non-Terminals and their various rules and Terminals -done
	//Fourth Mission: Print it all out -Done, sorta
     //Bug Squashing: TODO
	//Fifth: Error Handling -TODO

	//Any extra stuff later on

std::vector<LContainer> Execute(FILE*);

int main()
{
	Parser(Execute(fopen("Lexoutput.txt", "r"))); // We open the file
	
	return 0;
}

std::vector<LContainer> Execute(FILE* fin) {
	char        fileChar                     ; // to store a character from our file
	int         tempi      = 0               ; // A string index for tempString
	std::string tempString                   ; // C++ version of const char*. 
	LContainer  lc1                          ; // Initializes a class that will hold information about a Lexeme and Token type.
	bool        stringFlag = false, tokenFlag; // Flags for knowing stuff
	std::vector<LContainer> lcList;
	std::string::iterator strindex = tempString.begin();
	LContainer lcEOF("EOF", "EOF"); //EOF flag to tell the ptr of the vector that this is the last element in the array.

	while((fileChar = fgetc(fin)) != EOF) // Read from a file a character at a time. FIXME: EOF doesn't allow the last Token to be recorded from lexoutput.txt- logic error, do while loop?
	{
		
		if (fileChar != '\n' && fileChar != ' ' && fileChar != '=') // If we are not at the end of the file or at a space or an equal
		{
			stringFlag          = true;     //We are now reading a string
			tempString += fileChar; //The character will be saved into the string, the string index will be post incremented.
		}
		else if (fileChar == ' ' && stringFlag == true)
		{
			//tempString       += '\0' ;   //Since this is the end of the string
			lc1.setToken(tempString) ;   //In our proprietary Syntax Analyzer, there is a consistant format in our file, so we know that if theres a space, the previous string is a token.
			tempi             = 0    ;   //Our string index is reset
			tempString.clear()       ;	 //Our string is cleared.
			stringFlag        = false;   //We are no longer recording a string.

		}
		else if (fileChar == '\n' && stringFlag == true)
		{
			//tempString       += '\0' ;   //Since this is the end of the string
			lc1.setLexeme(tempString);	 //In our proprietary Syntax Analyzer, we know that at a newline, the previous string is a lexeme
			tempi             = 0    ;   //Our string index is reset
			tempString.clear()       ;	 //Our string is cleared.
			stringFlag        = false;   //We are no longer recording a string

			lcList.push_back(lc1);       //We will save each LContainer datatype in a vector to allow for seeking in the Parsing stage.
			lc1.clear();				 //Clears the LContainer for the next lines.
		}

	}
	lcList.push_back(lcEOF); // Push back the EOF into our vector.

	return lcList;
}