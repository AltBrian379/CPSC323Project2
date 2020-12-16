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
		LContainer lcDollar("$", "$");          //We push in the $ and Starting Point
		lcStack.push(lcDollar);
		LContainer lcStarter("NONTERMINAL", "S");
		lcStack.push(lcStarter);
	
	}

	std::cout << "Launching StackParser, Written by Brian Altamirano and Omar Mann\n\n";

	printToConsoleStringList(lcList, fout);

	std::cout << "Token: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	fprintf(fout, "\nToken: %s    Lexeme: %s\n", lcptr->getToken().c_str(), lcptr->getLexeme().c_str());

	do {

		sFlag = ProductionAction(lcptr,lcStack,fout);
	

	} while (lcptr->getLexeme() != "$" || sFlag == false);

	if (sFlag)
	{
		std::cout << "\nSuccess, the file is syntactically correct! \n Press Enter to Close the program...\n\n";
		printToFileb("\nSuccess, the file is syntactically correct!\n", fout);
	}
	else
	{
		std::cout << "\nERROR: Did not parse correctly.\n Press Enter to Close the program...";
		printToFileb("\nERROR: Did not parse correctly.\n", fout);
	}
	fclose(fout);
	std::cin.get();
	return;


}

void printToConsoleStringList(std::vector<LContainer> lclist, FILE* fout)
{
	std::cout << "String input: ";
	printToFileb("String input: ", fout);
	for (std::size_t i = 0; i < lclist.size(); ++i)
	{
		std::cout << lclist[i].getLexeme() << " ";
		fprintf(fout, "%s ", lclist[i].getLexeme().c_str());

	}
	std::cout << std::endl << std::endl; 
	fprintf(fout, "\n\n");
}

bool ProductionAction(LContainer*& lcptr, std::stack<LContainer>& lcStack,FILE* fout)
{
	Table parserTable;
	std::vector<LContainer> givenfromTable;
	LContainer poppedlcStack = lcStack.top();	// We save the top of the stack
	lcStack.pop();								// We pop the top element;

	if (poppedlcStack.getToken() == "NONTERMINAL")
	{
		printRule(poppedlcStack,fout);
		givenfromTable = parserTable.getTerminalString(lcptr, poppedlcStack);//Check the table using the current State
		if (givenfromTable[0].getToken().compare("epsilon") != 0) {
			for (std::size_t i = givenfromTable.size(); i != 0; --i)//Push the string to the stack
			{
				lcStack.push(givenfromTable[i - 1]);
			}
		}
		else { std::cout << "<Empty> -> epsilon\n";
		       printToFileb( "<Empty> -> epsilon\n", fout);}
	}
	else if (poppedlcStack.getToken() == "$")
	{
		//Do nothing, we are done with the stack
	}
	else if (poppedlcStack.getToken() != "NONTERMINAL")
	{
		std::cout << std::endl;
		printToFileb("\n", fout);
		Lexer(lcptr, fout); //Run Lexeme(); at this point we are just incrementing.
	}
	return true;
}

void Lexer(LContainer*& lcptr, FILE* fout)
{
	++lcptr;
	std::cout << "Token: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	printToFileb(lcptr, fout);
}

void printRule(LContainer givenLC,FILE* fout)
{
	if (givenLC.getLexeme() == "E")
	{
		std::cout << "<Expression> -> <Term> <ExpressionPrime>\n";
		printToFileb( "<Expression> -> <Term> <ExpressionPrime>\n", fout);
	}
	else if (givenLC.getLexeme() == "E'")
	{
		std::cout << "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>\n";
		printToFileb( "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>\n", fout);
	}
	else if (givenLC.getLexeme() == "T")
	{
		std::cout << "<Term> -> <Factor> <TermPrime>\n";
		printToFileb( "<Term> -> <Factor> <TermPrime>\n", fout);
	}
	else if (givenLC.getLexeme() == "T'")
	{
		std::cout << "<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>\n";
		printToFileb( "<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>\n", fout);
	}
	else if (givenLC.getLexeme() == "F")
	{
		std::cout << "<Factor> -> ( <Expression> ) | <ID> | <NUM>\n";
		printToFileb( "<Factor> -> ( <Expression> ) | <ID> | <NUM>\n", fout);
	}
	else if (givenLC.getLexeme() == "I")
	{
		std::cout << "<ID> -> id\n";
		printToFileb( "<ID> -> id\n", fout);
	}
	else if (givenLC.getLexeme() == "S")
	{
		std::cout << "<Statement> -> <Assignment> | <Declaritive>\n";
		printToFileb( "<Statement> -> <Assignment> | <Declaritive>\n", fout);
	}
	else if (givenLC.getLexeme() == "A")
	{
		std::cout << "<Assignment> -> <ID> = <Expression>; \n";
		printToFileb( "<Assignment> -> <ID> = <Expression>; \n", fout);
	}
	else if (givenLC.getLexeme() == "D")
	{
		std::cout << "<Declarative> -> <Type> <ID> <MoreIds>; \n";
		printToFileb( "<Declarative> -> <Type> <ID> <MoreIds>; \n", fout);
	}
	else if (givenLC.getLexeme() == "Y")
	{
		std::cout << "<Type> -> bool | float | int \n";
		printToFileb( "<Type> -> bool | float | int \n", fout);
	}
	else if (givenLC.getLexeme() == "N")
	{
		std::cout << "<NUM> -> num\n";
		printToFileb( "<NUM> -> num\n", fout);
	}
}
void printToFileb(std::string stringPrinted, FILE* fout) //Used to print a string to our file
{

	fprintf(fout, "%s", stringPrinted.c_str()); //c_str() returns a null terminated const char* of std::string
}

void printToFileb(LContainer*& lcptr, FILE* fout) //Used to print the Token and Lexeme
{
	//fout << "\nToken: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	fprintf(fout, "\nToken: %s    Lexeme: %s\n", lcptr->getToken().c_str(), lcptr->getLexeme().c_str());

}
