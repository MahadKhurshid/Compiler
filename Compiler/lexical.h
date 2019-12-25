#pragma once
#include<fstream>
#include<iostream>
#include<string.h>
#include<sstream>
#include"Table.h"
using namespace std;

#define MAXSIZE 50
#define STATES 57
#define TRANS_TOKENS_TYPE 25
#define TOKENS_TYPE 91

class lexical
{
private:

	// variables
	Table *symbolTable = nullptr;
	ifstream fin;
	ofstream foutTokens, foutError;
	char *buffer;
	char *tempBuffer;
	int bufferCount;
	int counter;
	int mapping[STATES][TRANS_TOKENS_TYPE];
	char mappingColumns[24];
	int map[255];
	int accStates[STATES];
	string keywords[10];
	string token_type[TOKENS_TYPE + 1];
	//	{
	//		3-28,89 index have Operators
	//		29-88 index have keywords
	//	}
	int lexicalErrors;
	// Private Funtions
	bool loadCode();
	char getChar();
	void loadTransTable();
	void loadTransColumns();
	void loadMap();
	void loadAcceptingStates();
	void loadToken_Types();
	void loadKeywords();
	string checkIfKeyword(string str);
	void makeToken(string value, int token_type);
	void ifErrorCame(string token, bool &flag, char ch);


public:

	lexical();
	lexical(Table *table);
	void runLexicalAnalyser();
	int getNoOfLexicalErrors();
	~lexical();

};