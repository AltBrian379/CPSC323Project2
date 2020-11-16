#include "Parser.h"

int Parser(std::vector<LContainer> lcList)
{
	LContainer* lcptr = &lcList.front();
	std::cout << "Token: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
	Statement(lcptr);
	std::cout << "\nSuccess I bet. If not it ill say so\n";
	std::cin.get();

	return 0;
}

void match(std::string terminal, LContainer* &lcptr) // This function is the end of a branch of the tree, as in the leaves. 
{
	if (lcptr->getLexeme().compare(terminal) == 0)
	{
			++lcptr;
			if (lcptr->getLexeme().compare("EOF") != 0)
			{
				std::cout << "\nToken: " << lcptr->getToken() << "    Lexeme: " << lcptr->getLexeme() << std::endl;
				return;
			}
	}
	else
	{
		std::cout << "\nThis statement not syntaxtically correct";
	}
	return;
}

void Expression(LContainer* &lcptr) // E -> TE'
{
	
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<Expression> -> <Term> <ExpressionPrime>\n";

	Term(lcptr);
	ExpressionPrime(lcptr);
	
}

void ExpressionPrime(LContainer* &lcptr) //E'-> +TE' | -TE' | EPSILON
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | EPSILON\n";

	if (lcptr->getLexeme().compare("+") == 0 ) //E' -> +TE'
	{
		
		match("+", lcptr);
		Term(lcptr);
		ExpressionPrime(lcptr);
	}
	else if (lcptr->getLexeme().compare("-") == 0) // E' -> -TE'
	{
		match("-", lcptr);
		Term(lcptr);
		ExpressionPrime(lcptr);
	}
	else { return; }  // E' -> EPSILON
}

void Term(LContainer* &lcptr) //T -> FT'
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<Type> -> <Factor> <TermPrime>\n";

	Factor(lcptr);
	TermPrime(lcptr);
}

void TermPrime(LContainer* &lcptr) // T' -> *FT' | /FT' | EPSILON
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | EPSILON\n";

	if (lcptr->getLexeme().compare("*") == 0) //T' -> *FT'
	{
		match("*", lcptr);
		Factor(lcptr);
		TermPrime(lcptr);
	}
	else if (lcptr->getLexeme().compare("/") == 0) // T' -> /FT'
	{
		match("/", lcptr);
		Factor(lcptr);
		TermPrime(lcptr);
	}
	else { return; }  // E' -> EPSILON
}

void Factor(LContainer* &lcptr) // F -> (E) | I | N
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<Factor> -> ( <Expression> ) | <ID> | <NUM>\n";

	if (lcptr->getLexeme().compare("(") == 0) // F-> (E)
	{
		match("(", lcptr);
		Expression(lcptr);
		match(")", lcptr);
	}
	else if (lcptr->getToken().compare("IDENTIFIER") == 0) // F -> I 
	{
		ID(lcptr);
	}
	else if (lcptr->getToken().compare("NUMBER") == 0) // F -> N
	{
		Num(lcptr);
	}
}

void ID(LContainer* &lcptr) // I -> id
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<ID> -> id\n";

	if (lcptr->getToken().compare("IDENTIFIER\0") == 0)
	{
		match(lcptr->getLexeme(), lcptr);
	}
	else
	{
		match("Error", lcptr);
	}
}

void Num(LContainer* &lcptr) // N -> num
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<NUM> -> num";

	if (lcptr->getToken().compare("NUMBER") == 0)
	{
		match(lcptr->getLexeme(), lcptr);
	}
	else
	{
		match("Error", lcptr);
	}
}

void Statement      (LContainer* & lcptr                  ) // S -> A | D
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<Statement> -> <Assignment> | <Declaritive>\n";

	if (lcptr->getToken().compare("IDENTIFIER") == 0)
	{
		Assign(lcptr);
	}
	else if (lcptr->getToken().compare("KEYWORD") == 0)
	{
		Declarative(lcptr);
	}
	
}


void Assign         (LContainer* & lcptr                   ) // A -> I=E;
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<Assign> -> <ID> = <Expressive>; \n";

	ID(lcptr);
	match("=", lcptr);
	Expression(lcptr);
	match(";", lcptr);

}

void Declarative    (LContainer* & lcptr                   ) // D -> YI
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<Declarative> -> <Type> <ID> \n";

	Type(lcptr);
	ID(lcptr);

}

void Type           (LContainer* & lcptr                   ) // Y -> bool | float | int
{
	if (lcptr->getLexeme().compare("EOF") != 0)
	std::cout << "<Type> -> bool | float | int \n";

	if(lcptr->getLexeme().compare("bool") == 0) // Y -> bool
	{
		match("bool", lcptr);
	}
	else if (lcptr->getLexeme().compare("float") == 0) // Y -> float
	{
		match("float",lcptr);
	}
	else if (lcptr->getLexeme().compare("int") == 0) // Y -> int
	{
		match("int",lcptr);
	}

}