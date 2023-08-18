/*Prototypes*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

int Lexile();
bool isSeperator(char x, char symbolBank[], int );
bool isOperator(char x, char operatorBank[], int );
void printString(char* givenstringArray, const char* keywordBank[], int keywordBankSize, bool &isNumber, FILE* fout);
bool CharBankCmp(char x, char bank[], int bankSize);
bool KeywordBankCmp(char* givenString, const char* givenStringBank[], int givenStringBankSize);