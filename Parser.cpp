#include "Parser.h"

int Parser(std::vector<LContainer> lcList)
{
	LContainer* lcptr = &lcList.front();
	Expression(lcptr, (&lcList.back()));
	std::cout << "\nSuccess I bet. If not it ill say so\n";
	std::cin.get();

	return 0;
}

LContainer* match(std::string terminal, LContainer* givenlc, LContainer* lcvend)
{
	if (givenlc->getLexeme().compare(terminal))
	{
		std::cout << "Token: " << givenlc->getToken() << "    Lexeme: " << givenlc->getLexeme() << std::endl;
	}
	else
	{
		std::cout << "\nThis statement not syntaxtically correct";
	}
	
	if (givenlc != lcvend) //FIXME: It's supposed to stop the program but something is wrong, will go on infinite loop.
		return ++givenlc;
	else
		return givenlc;
}

void Expression(LContainer* lcptr, LContainer* lcvend) // E -> TE'
{
	std::cout << "<Expression> -> <Term> <ExpressionPrime>\n";
	Term(lcptr, lcvend);
	ExpressionPrime(lcptr, lcvend);
	
}

void ExpressionPrime(LContainer* lcptr, LContainer* lcvend) //E'-> +TE' | -TE' | EPSILON
{
	std::cout << "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | EPSILON\n";
	if (lcptr->getLexeme().compare("+")) //E' -> +TE'
	{
		
		lcptr = match("+", lcptr, lcvend);
		Term(lcptr, lcvend);
		ExpressionPrime(lcptr, lcvend);
	}
	else if (lcptr->getLexeme().compare("-")) // E' -> -TE'
	{
		lcptr = match("-", lcptr, lcvend);
		Term(lcptr, lcvend);
		ExpressionPrime(lcptr, lcvend);
	}
	else { return; }  // E' -> EPSILON
}

void Term(LContainer* lcptr, LContainer* lcvend) //T -> FT'
{
	std::cout << "<Type> -> <Factor> <TermPrime>\n";
	Factor(lcptr, lcvend);
	TermPrime(lcptr, lcvend);
}

void TermPrime(LContainer* lcptr, LContainer* lcvend) // T' -> *FT' | /FT' | EPSILON
{
	std::cout << "<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | EPSILON\n";
	if (lcptr->getLexeme().compare("*")) //T' -> *FT'
	{
		lcptr = match("*", lcptr, lcvend);
		Factor(lcptr, lcvend);
		TermPrime(lcptr, lcvend);
	}
	else if (lcptr->getLexeme().compare("/")) // T' -> /FT'
	{
		lcptr = match("/", lcptr, lcvend);
		Factor(lcptr, lcvend);
		TermPrime(lcptr, lcvend);
	}
	else { return; }  // E' -> EPSILON
}

void Factor(LContainer* lcptr, LContainer* lcvend) // F -> (E) | I | N
{
	std::cout << "<Factor> -> ( <Expression> ) | <ID> | <NUM>\n";
	if (lcptr->getLexeme().compare("(")) // F-> (E)
	{
		lcptr = match("(", lcptr, lcvend);
		Expression(lcptr, lcvend);
		lcptr = match(")", lcptr, lcvend);
	}
	else if (lcptr->getToken().compare("IDENTIFIER")) // F -> I 
	{
		ID(lcptr, lcvend);
	}
	else if (lcptr->getToken().compare("NUMBER")) // F -> N
	{
		Num(lcptr, lcvend);
	}
}

void ID(LContainer* lcptr, LContainer* lcvend) // I -> id
{
	std::cout << "<ID> -> id\n";
	if (lcptr->getToken().compare("IDENTIFIER"))
	{
		lcptr = match(lcptr->getLexeme(), lcptr, lcvend);
	}
	else
	{
		lcptr = match("Error", lcptr, lcvend);
	}
}

void Num(LContainer* lcptr, LContainer* lcvend) // N -> num
{
	std::cout << "<NUM> -> num";
	if (lcptr->getToken().compare("NUMBER"))
	{
		lcptr = match(lcptr->getLexeme(), lcptr, lcvend);
	}
	else
	{
		lcptr = match("Error", lcptr, lcvend);
	}
}
