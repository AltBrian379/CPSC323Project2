#pragma once
#include "LContainer.h"
#include <vector>
#include <iostream>
#include <stdio.h>

int Parser          (std::vector<LContainer>              );

bool match          (std::string            ,LContainer* &, FILE*);

bool Expression     (LContainer* &,  FILE*);
bool ExpressionPrime(LContainer* &,  FILE*);
bool Term           (LContainer* &,  FILE*);
bool TermPrime      (LContainer* &,  FILE*);
bool Factor         (LContainer* &,  FILE*);
bool ID             (LContainer* &,  FILE*);
bool Num            (LContainer* &,  FILE*);

bool Statement      (LContainer* &,  FILE*);
bool Assign         (LContainer* &,  FILE*);

bool Declarative    (LContainer* &,  FILE*);
bool Type           (LContainer* &,  FILE*);

void printToFile(std::string stringPrinted, FILE* fout);
void printToFile(LContainer*& lcptr, FILE* fout);