#include "LContainer.h"
#include "Table.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stack>

void StackParser(std::vector<LContainer>);


//void printToFile(std::string stringPrinted, FILE* fout);
//void printToFile(LContainer*& lcptr, FILE* fout);
void printToConsoleStringList(std::vector<LContainer> lclist, FILE* fout);

bool ProductionAction(LContainer*& lcptr, std::stack<LContainer>& lcStack, FILE* fout);

void Lexer(LContainer*& lcptr, FILE* fout);

void printRule(LContainer givenLC, FILE* fout);

void printToFileb(std::string stringPrinted, FILE* fout);
void printToFileb(LContainer*& lcptr, FILE* fout);