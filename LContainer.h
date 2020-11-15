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
	
private:
	std::string _token;
	std::string _lexeme;
};

