#pragma once
#include "LContainer.h"
#include <vector>
#include <iostream>

int Parser(std::vector<LContainer>);

LContainer* match(std::string,LContainer*, std::size_t);

void Expression(LContainer*, LContainer*);
void ExpressionPrime(LContainer*, LContainer* lcvend);
void Term(LContainer*, LContainer* lcvend);
void TermPrime(LContainer*, LContainer* lcvend);
void Factor(LContainer*, LContainer* lcvend);
void ID(LContainer*, LContainer* lcvend);
void Num(LContainer*, LContainer* lcvend);

void Statement();
void Assign();

void Declarative();
void Type();

void match();