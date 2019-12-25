#include "Symbol.h"

Symbol::Symbol()
{
	next = list = 0;
}
Symbol::Symbol(char* s)
{
	strcpy_s(name, 20 ,s); 
	next = list = 0;
}
const char * Symbol::id()
{
	return name;
}
Symbol * Symbol::nextinlist()
{
	return list;
}
Symbol * Symbol::nextinbucket()
{
	return list;
}
Symbol::~Symbol()
{
	next = list = 0;
}
