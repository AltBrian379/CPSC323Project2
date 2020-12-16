#include "Parser.h"

int Parser(std::vector<LContainer> lcList) //Just checking real quick
{
	LContainer* lcptr = &lcList.front(); // Pointer to first element.
	bool sFlag = true; //flag to tell us if the stack parsed correctly
	FILE* fout = fopen("SyntaxOutput.txt", "w");

	std::cout << "Launching RDP Parser, Written by Brian Altamirano and Omar Mann\n\n";

	std::cout << "Token: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	printToFile(lcptr, fout);
	do {
		sFlag = Statement(lcptr, fout);
	} while (lcptr->getLexeme().compare("EOF") != 0 && sFlag);

	if (sFlag)
	{
		std::cout << "\nSuccess, the file is syntactically correct! \n Press Enter to Close the program...\n\n";
		printToFile("\nSuccess, the file is syntactically correct!\n", fout);
	}
	else
	{
		std::cout << "\nERROR: Did not parse correctly.\n Press Enter to Close the program...\n\n";
		printToFile("\nERROR: Did not parse correctly.\n", fout);
	}
	fclose(fout);
	std::cin.get();
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
	if (lcptr->getLexeme().compare("(") == 0) // F-> (E) | (E)
	{
		if (!match("(", lcptr, fout)) return false;
		if (!Expression(lcptr, fout)) return false;
		if (lcptr->getToken().compare("OPERATOR") == 0)
		{
			return true; // hotfix hardcoded. FIXME if i ever bother to.
		}
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

bool Statement      (LContainer* & lcptr, FILE * fout) // S -> A | D | if C then S else S endif | while C do S whileend | begin S Z end
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Statement> -> <Assignment> | <Declaritive> | if <Condition> then <Statement> else <Statement> endif |\nwhile <Condition> do <Statement> whileend | begin <Statement> <MoreStatements> end\n";
		printToFile("<Statement> -> <Assignment> | <Declaritive> |  if <Condition> then <Statement> else <Statement> endif |\nwhile <Condition> do <Statement> whileend | begin <Statement> <MoreStatements> end\n", fout);
	}

	
	if (lcptr->getLexeme().compare("if") == 0) // S -> if C then S else S endif
	{
		if(!match("if", lcptr, fout))	 return false;
		if(!Conditional(lcptr, fout))	return false;
		if(!match("then", lcptr, fout)) return false;
		if(!Statement(lcptr, fout))		return false;
		if(!match("else", lcptr,fout))	 return false;
		if(!Statement(lcptr, fout))		return false;
		if(!match("endif", lcptr, fout)) return false;
	}
	else if (lcptr->getLexeme().compare("while") == 0) // S -> while C do S whileend
	{
		if (!match("while", lcptr, fout))	 return false;
		if (!Conditional(lcptr, fout))	return false;
		if (!match("do", lcptr, fout)) return false;
		if (!Statement(lcptr, fout))		return false;
		if (!match("whileend", lcptr, fout))	 return false;
	}
	else if (lcptr->getLexeme().compare("begin") == 0) // begin S Z end
	{
		if (!match("begin", lcptr, fout))	 return false;
		if (!Statement(lcptr, fout))		return false;
		if (!MoreStatements(lcptr, fout)) return false;
		if (!match("end", lcptr, fout))	 return false;

	}
	else if (lcptr->getToken().compare("IDENTIFIER") == 0) // S -> A
	{
		if (!Assign(lcptr, fout)) return false;
	}
	else if (lcptr->getToken().compare("KEYWORD") == 0) // S -> D
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

bool Declarative    (LContainer* & lcptr, FILE * fout) // D -> YIM; | <empty>
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	{
		std::cout << "<Declarative> -> <Type> <ID> <MoreIds>; \n";
		printToFile("<Declarative> -> <Type> <ID> <MoreIds>; \n", fout);
	}
	if (lcptr->getToken().compare("KEYWORD") == 0) {
		if (!Type(lcptr, fout))			return false;
		if (!ID(lcptr, fout))			return false;
		if (!MoreIds(lcptr, fout))		return false;
		if (!match(";", lcptr, fout))	return false;
	}
	else { 
		std::cout << "<Empty> -> epsilon\n";
		printToFile("<Empty> -> epsilon\n", fout);
	}

	return true;

}

bool Type           (LContainer* & lcptr, FILE * fout) // Y -> bool | float | int
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Type> -> bool | float | int \n";
		printToFile("<Type> -> bool | float | int \n", fout);
	}

	if (lcptr->getLexeme().compare("bool") == 0) // Y -> bool
	{
		if (!match("bool", lcptr, fout)) return false;
	}
	else if (lcptr->getLexeme().compare("float") == 0) // Y -> float
	{
		if (!match("float", lcptr, fout)) return false;
	}
	else if (lcptr->getLexeme().compare("int") == 0) // Y -> int
	{
		if (!match("int", lcptr, fout)) return false;
	}
	else return false;

	return true;

}

bool MoreIds(LContainer* & lcptr, FILE* fout) // M -> ,IM | <empty>
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<MoreIds> -> , <ID> <MoreIds> | <empty> \n";
		printToFile("<MoreIds> -> , <ID> <MoreIds> | <empty> \n", fout);
	}

	if (lcptr->getLexeme().compare(",") == 0) {
		if(!match(",", lcptr, fout)) return false;
		if(!ID(lcptr, fout)) return false;
		if(!MoreIds(lcptr, fout)) return false;
	}
	else
	{
		std::cout << "<Empty> -> epsilon\n";
		printToFile("<Empty> -> epsilon\n", fout);
	}

	return true;
}

bool MoreStatements(LContainer*& lcptr, FILE* fout) // Z -> ; S Z | <empty>
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<MoreStatements> -> ; <Statement> <MoreStatements> | <empty> \n";
		printToFile("<MoreStatements> -> ; <Statement> <MoreStatements> | <empty> \n", fout);
	}

	if (lcptr->getLexeme().compare(";") == 0)
	{
		if (!match(";", lcptr, fout)) return false;
		if (!Statement(lcptr, fout)) return false;
		if (!MoreStatements(lcptr, fout)) return false;
	}
	else
	{
		std::cout << "<Empty> -> epsilon\n";
		printToFile("<Empty> -> epsilon\n", fout);
	}

	return true;

}
bool Conditional(LContainer*& lcptr, FILE* fout) // C -> E R E | E
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Conditional> -> <Expression> <Relop> <Expression> | <Expression> \n";
		printToFile("<Conditional> -> <Expression> <Relop> <Expression> | <Expression> \n", fout);
	}

	if (lcptr->getLexeme().compare("(") == 0)
	{
		match("(", lcptr, fout);
		if (!Expression(lcptr, fout)) return false;
		if (lcptr->getToken().compare("OPERATOR") == 0)
		{
			if (!Relop(lcptr, fout)) return false;
			if (!Expression(lcptr, fout)) return false;
			match(")", lcptr, fout);
		}
		else match(")", lcptr, fout);
	}
	else return false;

	return true;

}

bool Relop(LContainer*& lcptr, FILE* fout) //  R -> < | <= | == | <> | >= | >
{
	if (lcptr->getLexeme().compare("EOF") != 0) {
		std::cout << "<Relop> -> < | <= | == | <> | >= | > \n";
		printToFile("<Relop> -> < | <= | == | <> | >= | > \n", fout);
	}

	if (lcptr->getLexeme().compare("<") == 0)
	{
		if (!match("<", lcptr, fout)) return false;
		if (lcptr->getLexeme().compare("=") == 0)
		{
			if (!match("=", lcptr, fout)) return false;
		}
		else if (lcptr->getLexeme().compare(">") == 0)
		{
			if (!match(">", lcptr, fout)) return false;
		}
	}
	else if (lcptr->getLexeme().compare("=") == 0)
	{
		if (!match("=", lcptr, fout)) return false;
		if (!match("=", lcptr, fout)) return false;
	}
	else if (lcptr->getLexeme().compare(">") == 0)
	{
		if (!match(">", lcptr, fout)) return false;
		if (lcptr->getLexeme().compare("=") == 0)
		{
			if (!match("=", lcptr, fout)) return false;
		}

	}
	else return false;

	return true;
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

