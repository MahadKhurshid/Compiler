#include"lexical.h"
#include"Table.h"
#include"Parser.h"

void main(int argc, char const *argv[])
{
	//	Create Symbol Table
	Table *tb = new Table();
    //  Create lexical	Analyser
    lexical *lex = new lexical(tb);
	lex->runLexicalAnalyser();	// Run it to make tokens
	printf("Lexaical Errors : %d\n", lex->getNoOfLexicalErrors());
	cout << "======================================================================\n";
	cout << "Check Files: \n\t inputFiles/tokens.csv\t\t| Tokens";
	cout << "\n\t inputFiles/lexicalErrors.csv\t| Lexical Errors" << endl;
	cout << "\t inputFiles/parserErrors.csv\t| Parser Errors" << endl;
	cout << "======================================================================\n";
	//tb->printSymbolTable();
	delete lex;
	//	Create Parser
	Parser *par = new Parser();

	par->runParser();

	delete par;
	delete tb;
}
