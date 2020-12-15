#pragma once
#include <iostream>
class LContainer
{
public:
	std::string getToken();
	std::string getLexeme();

	void setToken(std::string);
	void setLexeme(std::string);

	void clear();

	/****Constructor********/
	LContainer();
	LContainer(std::string Token,std::string Lexeme);

	/***Instantaneous return(Not working and not used)****/
	LContainer makeLContainer(std::string Token, std::string Lexeme);
	
private:
	std::string _token;
	std::string _lexeme;
};

