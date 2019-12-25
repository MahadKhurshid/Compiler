#include "Table.h"


Table::Table()
{
	for (int i = 0; i < HT_SIZE; i++)
	{
		ht[i] = NULL;
	}
	first = last = 0;
	count = 0;
}
unsigned Table::hash(char *s)
{
	unsigned hval = 0; 
	while (*s != '\0') 
	{ 
		hval = (hval << 4) + *s; 
		s++; 
	}
	return hval;
}
Symbol * Table::clear()
{
	Symbol* list = first; 
	for (int i = 0; i<HT_SIZE; i++) 
		ht[i] = 0; 
	first = last = 0; 
	count = 0; 
	return list;
}
Symbol * Table::lookup(char * s)
{
	// Lookup name s in symbol table
	// Return pointer to found symbol
	// Return NULL if symbol not found

	unsigned h = hash(s);
	Symbol* sym = lookup(s, h);
	return sym;
}
Symbol * Table::lookup(char * s, unsigned h)
{
	// Lookup name s with hash value h
	// Hash value is passed to avoid its computation

	unsigned index = h % HT_SIZE; 
	Symbol* sym = ht[index]; 
	while (sym != 0) {
		if (strcmp(sym->name, s) == 0)
			break;
		sym = sym->next;
	}
	return sym;
}
Symbol * Table::lookupInsert(char * s)
{
	// Lookup first and then Insert name s
	// If name s exists then return pointer to its symbol
	// Otherwise, insert a new symbol and copy name s
	// Return address of newly added symbol

	unsigned h = hash(s) % HT_SIZE;	// Computed once
	Symbol* sym; 
	sym = lookup(s);	// Locate symbol first
	if (sym == 0)
	{
		// If not found
		sym = insert(s, h);// Insert a new symbol
	}
	return sym;
}
Symbol * Table::insert(char * s, unsigned h)
{
	// Insert name s with a given hash value h
	// New symbol is allocated
	// New symbol is inserted at front of a bucket list
	// New symbol is also linked at end of symbol list in table
	// Return pointer to newly allocated symbol
	
	unsigned index = h; 
	Symbol* sym = new Symbol(s); 
	sym->next = ht[index]; 
	ht[index] = sym; 
	if (count == 0)
	{
		first = last = sym;
	}
	else
	{
		last->list = sym;
		last = sym;
	}
	count++; 
	return sym;
}
void Table::printSymbolTable()
{
	Symbol* ptr1 = first;
	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\t\t*SYMBOL TABLE*";
	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n";
	while(ptr1 != NULL)
	{
		Symbol* ptr2 = ptr1;
		while (ptr2 != NULL)
		{
			cout << ptr2->name << "->";
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->list;
		cout << "\n";
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
}
Table::~Table()
{
	for (int i = 0; i < HT_SIZE; i++)
	{
		if (ht[i] != 0)
		{
			Symbol* ptr2 = ht[i];
			Symbol* prevptr = NULL;
			while (ptr2 != NULL)
			{
				prevptr = ptr2;
				ptr2 = ptr2->next;
				delete prevptr;
				prevptr = NULL;
			}
		}
	}
}
