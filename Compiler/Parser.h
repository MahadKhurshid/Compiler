#pragma once
#include<iostream>
#include<string.h>
#include<sstream>
#include<fstream>
#include"stack.h"
#include <cmath>

using namespace std;

class Tokens
{
public:
	string type;
	string token;
};

class Parser
{
private:
	ifstream tokenFile;
	ofstream parserErrors;
	stack st;
	int NoOfTerms;
	int NoOfNTerms;
	string *nonTerminals;
	string *Terminals;
	int **PTb;
	int **cfg;
	int NoOfProds;
	int LengthOfProd;
	Tokens tokens[100];
	int counter;
	int tokenCounter;
	string temptoken;
	char prevToken;

	// Private Funtions: 
	void loadCFG();
	void checkIfNtiIsExpr(int nti, int tokenNo);
	void loadParseTable();
	void loadTerminals();
	void loadNonTerminals();
	int getToken();
	int getTerminalIndex(string token);
	void loadTokens();

public:
	Parser();
	void runParser();
	~Parser();
};

