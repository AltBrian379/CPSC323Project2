#include "LContainer.h"

std::string LContainer::getToken()
{
	return _token;
}

std::string LContainer::getLexeme()
{
	return _lexeme;
}

void LContainer::setToken(std::string given)
{
	_token = given;
}

void LContainer::setLexeme(std::string given)
{
	_lexeme = given;
}

void LContainer::clear()
{
	_token.clear();
	_lexeme.clear();
}

LContainer::LContainer()
{
}

LContainer::LContainer(std::string Token, std::string Lexeme)
{
	setToken(Token);
	setLexeme(Lexeme);
}

LContainer LContainer::makeLContainer(std::string givenToken, std::string givenLexeme)
{
	LContainer returnLContainer(givenToken, givenLexeme);
	return returnLContainer;
}


