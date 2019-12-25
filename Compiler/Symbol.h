#include<string>

#pragma once
class Symbol
{
	friend class Table;
private:
	char   name[20];	// Symbol name
	Symbol* list;	// Next symbol in list 
	Symbol* next;	// Next symbol in bucket
public:
	Symbol();
	Symbol(char* s);	// Initialize symbol with name 
	const char* id();	// Return pointer to symbol name
	Symbol* nextinlist();	// Next symbol in list
	Symbol* nextinbucket();	// Next symbol in bucket
	~Symbol(); // Delete name and clear pointers
};

