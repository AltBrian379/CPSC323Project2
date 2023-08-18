#include "Table.h"

Table::Table()
{
	LContainer Empty("Empty", "Empty");
	/*Non-Terminals*/
	LContainer  Expression("NONTERMINAL", "E"), ExpressionPrime("NONTERMINAL", "E'"), Term("NONTERMINAL", "T"), TermPrime("NONTERMINAL", "T'"), Factor("NONTERMINAL", "F"),
		ID("NONTERMINAL", "I"), Statment("NONTERMINAL", "S"), Assign("NONTERMINAL", "A"), Declarative("NONTERMINAL", "D"), Type("NONTERMINAL", "Y"), Number("NONTERMINAL", "N"); // Nonterminals

	/*Terminals*/
	LContainer plus("TERMINAL","+"), minus("TERMINAL", "-"), multiply("TERMINAL", "*"), divide("TERMINAL", "/"), paraO("TERMINAL", "("), paraC("TERMINAL", ")"), identifier("TERMINAL", "id"),
		equal("TERMINAL", "="), semiC("TERMINAL", ";"), boolean("TERMINAL", "bool"), floatP("TERMINAL", "float"), integer("TERMINAL", "int"), number("TERMINAL", "num"), dollar("TERMINAL", "$"), epsilon("epsilon","epsilon"); // Terminals
	
	std::vector<std::vector<std::vector<LContainer>>> rulesTable  // First {} are our rows, Second {} are our columns, Third {} are our Tokens & Lexemes.
	{ //In summary, on this code Our X and Y axis are flipped, while on the table its correct, this is so that when we iterate to an elemnent
		// It will be correct. Ex: rulesTable[x][y][i]
		{{Empty},					{plus,Term,ExpressionPrime},		{Empty},				{epsilon},						{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // +

		{{Empty},					{minus,Term,ExpressionPrime},		{Empty},				{epsilon},						{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // -

		{{Empty},					{Empty},							{Empty},				{multiply,Factor,TermPrime},	{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // *

		{{Empty},					{Empty},							{Empty},				{divide,Factor,TermPrime},		{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // /

		{{Term,ExpressionPrime},	{Empty},							{Factor,TermPrime},		{Empty},						{paraO,Expression,paraC},		{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // (

		{{Empty},					{epsilon},							{Empty},				{epsilon},						{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // )

		{{Term,ExpressionPrime},	{Empty},							{Factor,TermPrime},		{Empty},						{ID},							{identifier},	{Assign},		{ID,equal,Expression,semiC},	{Empty},				{Empty},		{Empty}}, // id

		{{Empty},					{Empty},							{Empty},				{Empty},						{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // =

		{{Empty},					{epsilon},							{Empty},				{epsilon},						{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}}, // ;

		{{Empty},					{Empty},							{Empty},				{Empty},						{Empty},						{Empty},		{Declarative},	{Empty},						{Type,identifier},		{boolean},		{Empty}}, // bool

		{{Empty},					{Empty},							{Empty},				{Empty},						{Empty},						{Empty},		{Declarative},	{Empty},						{Type,identifier},		{floatP},		{Empty}}, // float

		{{Empty},					{Empty},							{Empty},				{Empty},						{Empty},						{Empty},		{Declarative},	{Empty},						{Type,identifier},		{integer},		{Empty}}, // int

		{{Term,ExpressionPrime},	{Empty},							{Factor,TermPrime},		{Empty},						{Number},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{number}}, // num

		{{Empty},					{Empty},							{Empty},				{Empty},						{Empty},						{Empty},		{Empty},		{Empty},						{Empty},				{Empty},		{Empty}} // $
		// E						E'									T						T'								F								I				->S				A								D						Y				N
	};

	_storedTable = rulesTable;
}

std::vector<LContainer> Table::getTerminalString(LContainer*& lcptr, LContainer poppedfromStack)
{
	std::vector <LContainer> retrievedTerminalString;
	int x_coord, y_coord; // Coordinate for our table search.
	 /*This first if else bundle finds out what our current element of our string input is. This will be our x.*/
	if (lcptr->getLexeme().compare("+") == 0)
	{
		x_coord = 0;
	}
	else if (lcptr->getLexeme().compare("-") == 0)
	{
		x_coord = 1;
	}
	else if (lcptr->getLexeme().compare("*") == 0)
	{
		x_coord = 2;
	}
	else if (lcptr->getLexeme().compare("/") == 0)
	{
		x_coord = 3;
	}
	else if (lcptr->getLexeme().compare("(") == 0)
	{
		x_coord = 4;
	}
	else if (lcptr->getLexeme().compare(")") == 0)
	{
		x_coord = 5;
	}
	else if (lcptr->getToken().compare("IDENTIFIER") == 0)
	{
		x_coord = 6;
	}
	else if (lcptr->getLexeme().compare("=") == 0)
	{
		x_coord = 7;
	}
	else if (lcptr->getLexeme().compare(";") == 0)
	{
		x_coord = 8;
	}
	else if (lcptr->getLexeme().compare("float") == 0)
	{
		x_coord = 9;
	}
	else if (lcptr->getLexeme().compare("int") == 0)
	{
		x_coord = 10;
	}
	else if (lcptr->getToken().compare("NUMBER") == 0)
	{
		x_coord = 11;

	}
	else if (lcptr->getLexeme().compare("$") == 0)
	{
		x_coord = 12;
	}


	/*This second will determine based on the top of the stack which NonTerminal got sent to determine y.*/
	if (poppedfromStack.getLexeme().compare("E") == 0)
	{
		y_coord = 0;
	}
	else if (poppedfromStack.getLexeme().compare("E'") == 0)
	{
		y_coord = 1;
	}
	else if (poppedfromStack.getLexeme().compare("T") == 0)
	{
		y_coord = 2;
	}
	else if (poppedfromStack.getLexeme().compare("T'") == 0)
	{
		y_coord = 3;
	}
	else if (poppedfromStack.getLexeme().compare("F") == 0)
	{
		y_coord = 4;
	}
	else if (poppedfromStack.getLexeme().compare("I") == 0)
	{
		y_coord = 5;
	}
	else if (poppedfromStack.getLexeme().compare("S") == 0)
	{
		y_coord = 6;
	}
	else if (poppedfromStack.getLexeme().compare("A") == 0)
	{
		y_coord = 7;
	}
	else if (poppedfromStack.getLexeme().compare("D") == 0)
	{
		y_coord = 8;
	}
	else if (poppedfromStack.getLexeme().compare("Y") == 0)
	{
		y_coord = 9;
	}
	else if (poppedfromStack.getLexeme().compare("N") == 0)
	{
		y_coord = 10;
	}

	retrievedTerminalString = _storedTable[x_coord][y_coord];

	return retrievedTerminalString;
}
