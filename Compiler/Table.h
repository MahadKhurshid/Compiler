#pragma once
#include"Symbol.h"
#include<iostream>
using namespace std;
const unsigned HT_SIZE = 300;// Hash Table Size

class Table
{
private:
	Symbol*  ht[HT_SIZE];	// Hash table
	Symbol*  first;	// First inserted symbol
	Symbol*  last;	// Last inserted symbol
	unsigned count;	// Symbol count
public:
	Table();
	unsigned hash(char * s);
	Symbol* clear();	// Clear symbol table
	Symbol* lookup(char*s);	// Lookup name s
	Symbol* lookup(char*s,unsigned h);	// Lookup s with hash h
	Symbol* insert(char*s,unsigned h);	// Insert s with hash h
	Symbol* lookupInsert(char*s);	// Lookup and insert s
	Symbol* symlist() {return first;}	// List of symbols
	unsigned symbols(){return count;}	// Symbol count
	void printSymbolTable();
	~Table();
};

