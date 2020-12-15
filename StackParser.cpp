#include "StackParser.h"



void StackParser(std::vector<LContainer> lcList)
{
	LContainer* lcptr = &lcList.front();			// Pointer to first element.
	bool sFlag = true;								//flag to tell us if the stack parsed correctly
	FILE* fout = fopen("StackSyntaxOutput.txt", "w");    //We open this file to allow for us to output.

	/*We replace our EOF with a $ for table parser.*/
	lcList.back().setLexeme("$");
	lcList.back().setToken("$");
	/*We replace our EOF with a $ for table parser.*/

	std::stack<LContainer> lcStack;

	{
		LContainer lcDollar("$", "$");
		lcStack.push(lcDollar);
		LContainer lcStarter("NONTERMINAL", "S");
		lcStack.push(lcStarter);
	
	}
	printToConsoleStringList(lcList);




	// USED for RDP std::cout << "Token: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	//printToFile(lcptr, fout);
	do {

		sFlag = ProductionAction(lcptr,lcStack);
		// Used for RDP--sFlag = Statement(lcptr, fout);

	} while (lcptr->getLexeme() != "$" || sFlag == false);

	if (sFlag)
	{
		std::cout << "\nSuccess, the file is syntactically correct! \n Press Enter to Close the program...";
		//printToFile("\nSuccess, the file is syntactically correct!\n", fout);
	}
	else
	{
		std::cout << "\nERROR: Did not parse correctly.\n Press Enter to Close the program...";
		//printToFile("\nERROR: Did not parse correctly.\n", fout);
	}
	fclose(fout);
	std::cin.get();
	return;


}

void printToConsoleStringList(std::vector<LContainer> lclist)
{
	std::cout << "String input: ";
	for (std::size_t i = 0; i < lclist.size(); ++i)
	{
		std::cout << lclist[i].getLexeme() << " ";

	}
	std::cout << std::endl; 
}

bool ProductionAction(LContainer*& lcptr, std::stack<LContainer>& lcStack)
{
	Table parserTable;
	std::vector<LContainer> givenfromTable;
	LContainer poppedlcStack = lcStack.top();	// We save the top of the stack
	lcStack.pop();								// We pop the top element;

	if (poppedlcStack.getToken() == "NONTERMINAL")
	{
		givenfromTable = parserTable.getTerminalString(lcptr, poppedlcStack);//Check the table using the current State
		if (givenfromTable[0].getToken().compare("epsilon") != 0) {
			for (std::size_t i = givenfromTable.size(); i != 0; --i)//Push the string to the stack
			{
				lcStack.push(givenfromTable[i - 1]);
			}
		}
	}
	else if (poppedlcStack.getToken() == "$")
	{
		//Do nothing, we are done with the stack
	}
	else if (poppedlcStack.getToken() != "NONTERMINAL")
	{
		Lexeme(lcptr); //Run Lexeme(); at this point we are just incrementing.

	}
	return true;
}

void Lexeme(LContainer*& lcptr)
{
	++lcptr;
}

//void printToFile(std::string stringPrinted, FILE* fout) //Used to print a string to our file
//{
//
//	fprintf(fout, "%s", stringPrinted.c_str()); //c_str() returns a null terminated const char* of std::string
//}
//
//void printToFile(LContainer*& lcptr, FILE* fout) //Used to print the Token and Lexeme
//{
//	//fout << "\nToken: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
//	fprintf(fout, "\nToken: %s    Lexeme: %s\n", lcptr->getToken().c_str(), lcptr->getLexeme().c_str());
//
//}
