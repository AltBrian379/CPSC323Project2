#include "LContainer.h"
#include "Table.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stack>

void StackParser(std::vector<LContainer>);


//void printToFile(std::string stringPrinted, FILE* fout);
//void printToFile(LContainer*& lcptr, FILE* fout);
void printToConsoleStringList(std::vector<LContainer> lclist);

bool ProductionAction(LContainer*& lcptr, std::stack<LContainer>& lcStack);

void Lexeme(LContainer*& lcptr);