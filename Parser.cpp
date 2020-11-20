#include "Parser.h"

int Parser(std::vector<LContainer> lcList) //Just checking real quick
{
	LContainer* lcptr = &lcList.front();
	bool sFlag = true;
	FILE* fout = fopen("syntaxoutput.txt", "w");

	std::cout << "Token: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	printToFile(lcptr, fout);
	do {
		sFlag = Statement(lcptr, fout);
	} while (lcptr->getLexeme().compare("EOF") != 0 && sFlag);

	if (sFlag)
	{
		std::cout << "\nSuccess I bet. If not it ill say so\n";
		printToFile("\nSuccess I bet. If not it ill say so\n", fout);
	}
	else
	{
		std::cout << "\nERROR: Did not parse correctly.\n";
		printToFile("\nERROR: Did not parse correctly.\n", fout);
	}
	std::cin.get();
	fclose(fout);
	return 0;
}

bool match(std::string terminal, LContainer* &lcptr, FILE * fout) // This function is the end of a branch of the tree, as in the leaves. 
{
	if (lcptr->getLexeme().compare(terminal) == 0) // if the Lexeme in the string is equal to the terminal...
	{
			++lcptr; //...Increment the pointer
			if (lcptr->getLexeme().compare("EOF") != 0) // If it is not the final element, print out the new element and return true
			{
				std::cout << "\nToken: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
				printToFile(lcptr, fout);
				return true;
			}
			else
			{
				return true; //Otherwise if we are on the final element, just return true.
			}
	}
	else //else we declare that the statement is not syntactically correct, and return false.
	{
		std::cout << "\nThis statement not syntactically correct\n";
		printToFile("\nThis statement not syntactically correct\n", fout);
		return false;
	}
}

bool Expression(LContainer* &lcptr, FILE * fout) // E -> TE'
{
	
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Expression> -> <Term> <ExpressionPrime>\n";
		printToFile("<Expression> -> <Term> <ExpressionPrime>\n", fout);
	}

	if (!Term(lcptr, fout)) { return false; }					//if the Nonterminal returns false when given a token, then we return false.
	if (!ExpressionPrime(lcptr, fout)) { return false; }

	return true; //If the Tokens given were valid, then we return true
	
}

bool ExpressionPrime(LContainer* &lcptr, FILE * fout) //E'-> +TE' | -TE' | <Empty>
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>\n";
		printToFile("<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>\n", fout);
	}
	if (lcptr->getLexeme().compare("+") == 0 ) //E' -> +TE'
	{
		
		if (!match("+", lcptr, fout)) { return false; }
		if (!Term(lcptr, fout)) { return false; }
		if (!ExpressionPrime(lcptr, fout)) { return false; };

	}
	else if (lcptr->getLexeme().compare("-") == 0) // E' -> -TE'
	{
		if (!match("-", lcptr, fout)) { return false; }
		if (!Term(lcptr, fout)) { return false; }
		if (!ExpressionPrime(lcptr, fout)) { return false; }
	}
	else  // E' -> <EMPTY>
	{
		std::cout << "<Empty> -> epsilon\n";
		printToFile("<Empty> -> epsilon\n", fout);
	} 
	return true;
}

bool Term(LContainer* &lcptr, FILE * fout) //T -> FT'
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Term> -> <Factor> <TermPrime>\n";
		printToFile("<Term> -> <Factor> <TermPrime>\n", fout);
	}

	if (!Factor(lcptr, fout)) { return false; }
	if (!TermPrime(lcptr, fout)) { return false; }

	return true;
}

bool TermPrime(LContainer* &lcptr, FILE * fout) // T' -> *FT' | /FT' | <Empty>
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>\n";
		printToFile("<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>\n", fout);
	}

	if (lcptr->getLexeme().compare("*") == 0) //T' -> *FT'
	{
			if(!match("*", lcptr, fout)) { return false; }
			if(!Factor(lcptr, fout)) return false;
			if(!TermPrime(lcptr, fout)) return false;
	}
	else if (lcptr->getLexeme().compare("/") == 0) // T' -> /FT'
	{
		if (!match("/", lcptr, fout)) return false;
		if (!Factor(lcptr, fout)) return false;
		if (!TermPrime(lcptr, fout)) return false;
	}
	else // E' -> <EMPTY>
	{
		std::cout << "<Empty> -> epsilon\n";
		printToFile("<Empty> -> epsilon\n", fout);
	}  
	return true;
}

bool Factor(LContainer* &lcptr, FILE * fout) // F -> (E) | I | N
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Factor> -> ( <Expression> ) | <ID> | <NUM>\n";
		printToFile("<Factor> -> ( <Expression> ) | <ID> | <NUM>\n", fout);
	}
	if (lcptr->getLexeme().compare("(") == 0) // F-> (E)
	{
		if (!match("(", lcptr, fout)) return false;
		if (!Expression(lcptr, fout)) return false;
		if (!match(")", lcptr, fout)) return false;
	}
	else if (lcptr->getToken().compare("IDENTIFIER") == 0) // F -> I 
	{
		if (!ID(lcptr, fout)) return false;
	}
	else if (lcptr->getToken().compare("NUMBER") == 0) // F -> N
	{
		if (!Num(lcptr, fout)) return false;
	}
	else return false;

	return true;
}

bool ID(LContainer* &lcptr, FILE * fout) // I -> id
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<ID> -> id\n";
		printToFile("<ID> -> id\n", fout);
	}

	if (!match(lcptr->getLexeme(), lcptr, fout)) { return false; }

	return true;

}

bool Num(LContainer* &lcptr, FILE * fout) // N -> num
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<NUM> -> num\n";
		printToFile("<NUM> -> num\n", fout);
	}

		
	if (!match(lcptr->getLexeme(), lcptr, fout)) return false;

	return true;

}

bool Statement      (LContainer* & lcptr, FILE * fout) // S -> A | D
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Statement> -> <Assignment> | <Declaritive>\n";
		printToFile("<Statement> -> <Assignment> | <Declaritive>\n", fout);
	}
	if (lcptr->getToken().compare("IDENTIFIER") == 0)
	{
		if (!Assign(lcptr, fout)) return false;
	}
	else if (lcptr->getToken().compare("KEYWORD") == 0)
	{
		if (!Declarative(lcptr, fout)) return false;
	}
	else return false;

	return true;
	
}


bool Assign         (LContainer* & lcptr, FILE * fout) // A -> I=E;
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Assignment> -> <ID> = <Expression>; \n";
		printToFile("<Assignment> -> <ID> = <Expression>; \n", fout);
	}
	if (!ID(lcptr, fout)) return false;
	if (!match("=", lcptr, fout)) return false;
	if (!Expression(lcptr, fout)) return false;
	if (!match(";", lcptr, fout)) return false;

	return true;

}

bool Declarative    (LContainer* & lcptr, FILE * fout) // D -> YI
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	{
		std::cout << "<Declarative> -> <Type> <ID> \n";
		printToFile("<Declarative> -> <Type> <ID> \n", fout);
	}

	if (!Type(lcptr, fout)) return false;
	if (!ID(lcptr, fout)) return false;

	return true;

}

bool Type           (LContainer* & lcptr, FILE * fout) // Y -> bool | float | int
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Type> -> bool | float | int \n";
		printToFile("<Type> -> bool | float | int \n", fout);
	}

	if(lcptr->getLexeme().compare("bool") == 0) // Y -> bool
	{
		if(!match("bool", lcptr, fout)) return false;
	}
	else if (lcptr->getLexeme().compare("float") == 0) // Y -> float
	{
		if (!match("float",lcptr, fout)) return false;
	}
	else if (lcptr->getLexeme().compare("int") == 0) // Y -> int
	{
		if (!match("int",lcptr, fout)) return false;
	}

	return false;

}


void printToFile(std::string stringPrinted, FILE * fout) //Used to print a string to our file
{

	fprintf(fout, "%s", stringPrinted.c_str()); //c_str() returns a null terminated const char* of std::string
}

void printToFile(LContainer* &lcptr, FILE * fout) //Used to print the Token and Lexeme
{
	//fout << "\nToken: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	fprintf(fout, "\nToken: %s    Lexeme: %s\n", lcptr->getToken().c_str(), lcptr->getLexeme().c_str());

}