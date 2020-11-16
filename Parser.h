#pragma once
#include "LContainer.h"
#include <vector>
#include <iostream>

int Parser          (std::vector<LContainer>              );

void match          (std::string            ,LContainer* &);

void Expression     (LContainer* &                        );
void ExpressionPrime(LContainer* &                        );
void Term           (LContainer* &                        );
void TermPrime      (LContainer* &                        );
void Factor         (LContainer* &                        );
void ID             (LContainer* &                        );
void Num            (LContainer* &                        );

void Statement      (LContainer* &                        );
void Assign         (LContainer* &                        );

void Declarative    (LContainer* &                        );
void Type           (LContainer* &                        );