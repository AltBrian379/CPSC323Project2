# CPSC323 Project 2 Syntax Analysis Parser
An implementation of a lexile and syntax analyzer. It is implemented using Recusrive Descent Parsing and Top Down Predictive Parsing table with pre-defined grammar rules. 

# The Project
## Problem Statement
Adding a table driven parser using a stack to syntax analyzer. Analyzes if a given input statement is lexically and  syntactically correct  by using predefined grammar rules.The analyzer must be built using a top-down parser method.

Since we started with the RDP method, we will now implement the grammar using the Stack Table approach.

This program runs a lexical analyzer, then 2 variations of syntax analysis, a recursive descent parser AND a Table Driven Parser using the stack approach.

## How to use your program 
These are the files necessary for program execution:

LContainer.cpp  	LContainer.h 
Lexile.cpp 		    Lexile.h 
Parser.cpp 		    Parser.h 
Table.cpp		      Table.cpp 
StackParser.cpp 	StackParser.h
main.cpp

input.txt  - source code to be analyzed
SyntaxAnalyzer.exe - executable file

In order to use the program: create/place a text file with the contents of what is to be analyzed in the same directory of the executable file(main.cpp) and name it “input.txt”.

After running the executable,in the same directory, the program will create the result of the lexical analysis first  in a text file named “Lexoutput.txt”.

The program will then create the “syntaxoutput.txt” file which is the output of the program from the recursive descent parser.It will also create StackSyntaxOutput.txt as the output for the table driven parser as the final output.

## Design of Program

### Implementation  using top-down parser method of Recursive Descent Parsing (RDP)
The syntax analyzer integrates our lexical analyzer(Lexile.cpp, Lexile.h)to produce an input that is acceptable for the program.The input.txt is  first sent through our lexical analyzer and sends the output to then do the syntax analysis.

The program uses the LContainer class to set and get tokens and lexemes from the output . contained in the files: LContainer.cpp & LContainer.h

The syntax analyzer is defined by certain grammar rules that are predefined, and explains how the given statement should be classified. Only if these grammar rules are followed properly can it be determined if the syntax is correct for each statement.

Each Nonterminal has its grammar rules defined in its own function. We then test the given statement in the matching function to see if it applies according to the defined grammar rules .

For Table:
	Non Terminals and Terminals are used to construct the table while each cell contains the appropriate string of Terminals and Nonterminals to push into the stack

### Grammar Rules for RDP

Symbols Bank

  E= \<Expression>	T= \<Term>		F= \<Factor>		ε = \<Empty>
	
  N = \<Number>	I = \<ID>		S= \<Statement>

  A= \<Assign>		D= \<Declarative> 	Y= \<Type>		M = \<MoreIds>

  Z = \<MoreStatements> 	C = \<Conditionals>  	R = \<Relop>

  Nonterminals={E,E’,T,T’,F,I,S,A,D,Y}

  Terminals={ + , - , * , / , ( , ) , id , = , ; , bool, float, int , ε}

#### For Arithmetic Expressions: (removed left recursion)

  E  -> TE’

  E’ -> +TE’ | -TE’ | ε

  T  ->  FT’

  T’ -> *FT’ | /FT’ | ε

  F  ->  (E) | N | I

  I  ->  id 

#### For Assignment statements: 

  S  ->  A

  A  ->  I = E;

#### For Declarative statements:

  S  ->  D
 
  D  ->  Y I
 
  Y  ->  bool | float | int

#### For If-While statements:

  S  ->  if C then S else S endif | while C do S whileend | begin S Z end

  Z -> ; S Z | ε

  C -> E R E | E

  R -> < | <= | == | <> | >= | >

One version of the syntax analyzer uses the Recursive Descent Parser method of implementation. When the given token/lexeme is passed to a Nonterminal function, if the grammar rule includes for example E’ -> +TE’, In function E’(),we check if the lexeme follows the format of ‘+’ followed by a T and then E.We can only say E’() is true if all 3 are true.call function T and recursively have to call E’().

### Implementation  using top-down parser method of Predictive Table parsing (stack approach)

This implementation of the top-down parser attempts to limit the amount of backtracking that the RDP may face if grammar whose right hand side starts with  nonterminals. It has the ability to look ahead in the grammar to anticipate which terminals can be derived from different nonterminals on the right hand side.
For the given grammar , we create a First set, the set of all possible firsts for each nonterminal in the grammar. We also create Follow sets for each of the nonterminals,which is the set of all terminals that could come after the nonterminals.

#### First Set & Follow Set

TODO: Upload image

Using these First and Follow sets, we create the Parsing Table,  which defines for each nonterminal, which right hand side rule we will select.

#### Stack (container adapter)
This implementation makes use of a stack to keep track of possible terminal/nonterminals based on the grammar.The stack is given a starting symbol “$” which is pushed onto the stack and onto the back of the input string. This signals if our stack is empty and tells us if our analyzer has succeeded or failed.The starting nonterminal is pushed onto the stack along with the starting symbol. We pop nonterminals and push their right hand side rules from the table for the matching terminal. the process continues until we reach the desired terminal. 

### Parsing Table

TODO: Parsing Table image

## Major Product Functions 

Lexical Analyzer - 
Lexile() -reads source code on the text file and gives the token type and lexeme of keywords,identifiers operators,etc.

Syntax Analyzer (Recursive Descent Parser) - 
int Parser() - this function is the main function of the program that gets the token and lexeme from syntaxoutput.txt and loops through it and begins the syntax analysis with Statement() function call. Contains error messages if not parsed correctly.

bool match() - this function compares the given lexeme to the terminals, essentially being the leaves to the grammar structure tree, it is here that the given statement is declared either syntactically correct or not.

bool Expression() -calls functions Term() and ExpressionPrime(),if both are true. returns true for this product. grammar  rule E -> TE'

bool ExpressionPrime() - checks for + or - and calls Term() , and recursively calls itself according to the grammar rule +TE' or -TE'. Otherwise it is empty for rule epsilon  E' -> ε.

bool Term() - calls functions Factor() and TermPrime(),if both are true. returns true for this product. grammar rule T -> FT'

bool TermPrime() - checks for *  or / and calls Factor() , and recursively calls itself according to the grammar rule *FT' or /FT'. Otherwise it is empty and returns true for rule epsilon  T' -> ε.

bool Factor() - Used to verify if lexeme is a factor using  F -> (E) | I | N rules. Checks to see if the current lexeme is “(“ with match(), if it is, then calls bool Expression(),followed by match() for “)”. All 3 need to be true for the function to return true. The function can instead call for ID() or Num() if the token matches.

bool Id() - matches lexeme to the terminal id and if so, returns true

bool Num() - matches lexeme to the terminal num and if so, returns true

bool Statement() - verifies if a token is a statement using Assign() or Declarative(). For grammar rule S -> A | D
bool Assign() - verifies assignment operations using A -> I=E; grammar rule. calls ID() match() for ‘=’ and ‘;’ and Expression().

bool Declarative() - verifies  declarative statement using D -> YI rule. Calls Type() and ID() successively.

bool Type() - verifies if lexeme is a type by using match() with either a “bool”, “float” or “int”. following grammar rules Y -> bool | float | int.

Syntax Analyzer (Predictive Table Parser ) -

Table() - contains the parsing table  based on the given expression of grammar.  Rows represent nonterminals, Columns represent terminal symbols
getTerminalString() - 
StackParser() - main parsing function that initializes stack with starting symbol & places it on the input string. This function contains the while loop structure that continues until the stack is empty.
ProductionAction()- function contained in the while loop of StackParser, controls the pushes and pops on the stack  for the current token
Lexer() - Increments the pointer of the input string when a terminal is popped from the stack.

# Limitations
The program is limited to the file type that can be taken as input and the output type. The program can only take in txt files named “input.txt” and will only output files called “Lexoutput.txt” & “syntaxoutput.txt”. 

The program is also limited to what it can take in as tokens. If it is not a cased alphabetical or a number, or a symbol included in the symbol list hardcoded within the program, it will not be mentioned, and will not display an error. However as long as it was included in the list of the example, it will be recognized, including spaces.

The length of an individual string (Dynamically allocated char*) will also be limited by the BUFSIZ set by the C standard library. 

As far as the rules go:
RDP:
We can initialize and then assign a value, but we cannot do both on the same line;

Table:
It does not have an in depth error handling besides calling that the string is syntactically incorrect.

# 5. Shortcomings

The if-else implementation is not complete, and there is a bug when doing so. As of now, the only iterations that function are, Assignment, Declaration, Expressions, and Initialization.
Due to time constraints, not able to complete the list of major functions for Conditional(),MoreID(),MoreStatements(), Relop().

Table Parser:
The only rules that were implemented in the table were the arithmetic expressions, Assignment statement, and Declarative statements.



If-Else and While-do are not functioning correctly. Endif causes issues.


