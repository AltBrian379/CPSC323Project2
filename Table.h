#pragma once
#include <vector>
#include "LContainer.h"
class Table
{

public:

	Table(); //Constructor for Table.
	std::vector<LContainer> getTerminalString(LContainer*& lcptr, LContainer poppedfromStack);

private:

	std::vector<std::vector<std::vector<LContainer>>> _storedTable;

};

