#include "Parser.h"

Parser::Parser()
{
	tokenFile.open("ioFiles/tokens.csv", ios::in);
	parserErrors.open("ioFiles/parserErrors.txt", ios::out);
	tokenCounter = 0;
	counter = 0;
	NoOfNTerms = 0;
	NoOfProds = 0;
	LengthOfProd = 0;
	NoOfTerms = 0;
	Terminals = NULL;
	nonTerminals = NULL;
	loadNonTerminals();
	loadTerminals();
	loadParseTable();
	loadCFG();
	loadTokens();
}
void Parser::loadTerminals()
{
	ifstream fin;
	fin.open("ioFiles/terminals.txt", ios::in);
	fin >> NoOfTerms;
	NoOfTerms++;
	Terminals = new string[NoOfTerms];
	for (int i = 1; i < NoOfTerms; i++)
	{
		fin >> Terminals[i];
	}
	fin.close();
}
void Parser::loadNonTerminals()
{
	ifstream fin;
	fin.open("ioFiles/non-terminals.txt", ios::in);
	fin >> NoOfNTerms;
	nonTerminals = new string[NoOfNTerms];
	for (int i = 1; i < NoOfNTerms; i++)
	{
		fin >> nonTerminals[i];
	}
	fin.close();
}
int Parser::getToken()
{
	if (counter >= tokenCounter)
	{
		loadTokens();
		if (tokens[0].token == "") return -999;
	}
	counter++;
	temptoken = tokens[counter - 1].token;
	if (tokens[counter - 1].type == "Num") return 4;
	if (tokens[counter - 1].type == "Id") return 3;

	// Search token in Terminals
	return getTerminalIndex(tokens[counter - 1].token);
}
int Parser::getTerminalIndex(string token)
{
	for (int i = 1; i < NoOfTerms; i++)
	{
		if (token == Terminals[i] && i != 3 && i != 4)
		{
			return i;
		}
	}
	return 999;
}
void Parser::loadTokens()
{
	string str;
	string tempToken;
	memset(tokens, 0, 100);
	for (tokenCounter = 0; tokenCounter < 99 && !tokenFile.eof(); tokenCounter++)
	{
		getline(tokenFile, str);
		tokens[tokenCounter].type = str.substr(0, str.find(","));
		tokens[tokenCounter].token = str.substr(str.find(",") + 1, str.length());
		if ((tokens[tokenCounter].token[0] == '+' || tokens[tokenCounter].token[0] == '-') && tokens[tokenCounter].type == "Num" && prevToken != '(')
		{
			tempToken = tokens[tokenCounter].token.substr(1, str.length());
			tokens[tokenCounter].token = tokens[tokenCounter].token[0];
			tokens[tokenCounter+1].token = tempToken;
			tokens[tokenCounter+1].type = tokens[tokenCounter].type;
			tokens[tokenCounter].type = tokens[tokenCounter].token;
			tokenCounter++;
		}
		if (tokens[tokenCounter].type == "Num") prevToken = NULL;
		if (tokens[tokenCounter].token == "(") prevToken = tokens[tokenCounter].token[0];
		if (tokens[tokenCounter].token == "") break;
	}
}
void Parser::loadParseTable()
{
	// -998 -> pop | -997 -> skip
	ifstream fin;
	fin.open("ioFiles/parseTable.txt", ios::in);
	PTb = new int*[NoOfNTerms];
	for (int i = 0; i < NoOfNTerms; i++)
	{
		PTb[i] = new int[NoOfTerms-1];
	}
	for (int i = 0; i < NoOfNTerms; i++)
	{
		for (int j = 0; j < NoOfTerms-1; j++)
		{
			fin >> PTb[i][j];
		}
	}
	fin.close();
}
void Parser::loadCFG()
{
	ifstream fin;
	fin.open("ioFiles/cfg.txt", ios::in);
	fin >> NoOfProds;
	fin >> LengthOfProd;
	cfg = new int*[NoOfProds];
	for (int i = 0; i < NoOfProds; i++)
	{
		cfg[i] = new int[LengthOfProd];
	}
	for (int i = 0; i < NoOfProds; i++)
	{
		for (int j = 0; j < LengthOfProd; j++)
		{
			fin >> cfg[i][j];
			if (cfg[i][j] == -999)
			{
				break;
			}
		}
	}
	fin.close();
}
void Parser::checkIfNtiIsExpr(int nti, int tokenNo)
{
	if (nti == 20)
	{
		string token = temptoken;
		int newtoken = getToken();
		if (Terminals[newtoken] == ":=")
		{
			PTb[nti][tokenNo] = 35;
		}
		else
		{
			PTb[nti][tokenNo] = 36;
		}
		temptoken = token;
		counter--;
	}
}
void Parser::runParser()
{
	st.push(0);	//	Push First Non-terminal
	int tokenNo;
	int flag; int nti; // Non Terminal Index :)
	int *arr = new int[LengthOfProd];
	while (true)
	{
		tokenNo = getToken();
		if (tokenNo == 999) // if Rule Doesn't exist for Token
		{
			parserErrors << "<" << tokens[counter - 1].type << "," << tokens[counter - 1].token << ">" << endl;
			continue;
		}
		if (tokenNo == -999)	//	If tokens are End
		{
			break;
		}
		flag = false;
		tokenNo--;
		while (!flag)	// Run Until token not found!
		{
			nti = st.pop();
			if (nti < 0)
			{
				nti = abs(nti);
				if (tokenNo +1 == nti)
				{
					cout << temptoken << ", Parsed\n";
					flag = true;
					continue;
				}
			}
			if (PTb[nti][tokenNo] >= 0)	// If Rule Does Exist!
			{
				// Checking if Non-terminal is Expr 
				checkIfNtiIsExpr(nti, tokenNo);
				int index = 0;
				for (int i = 0; i < LengthOfProd; i++)
				{
					// Check CFG's Rule Mentioned by Parse-table
					// if CFG Ends
					if (cfg[PTb[nti][tokenNo]][i] == -999) break;
					// if Null production came
					if (cfg[PTb[nti][tokenNo]][i] == 999) break;
					if (cfg[PTb[nti][tokenNo]][i] < 0)
					{
						int num = cfg[PTb[nti][tokenNo]][i];
						num *= (-1);
						if (tokenNo +1 == num)
						{
							cout << temptoken << ", Parsed\n";
							flag = true;
							continue;
						}
					}
					arr[index++] = cfg[PTb[nti][tokenNo]][i];	// Load all Productions Of Non-terminal
				}
				for (int i = index-1; i >= 0; i--)	//	In Reverse Order
				{
					st.push(arr[i]);
				}
			}
			else if(PTb[nti][tokenNo] == -998)	// if Pop Occur	
			{
				if(tokens[counter-2].type != "(" && tokens[counter - 1].type != ")")
					parserErrors << "<"<<tokens[counter - 1].type << "," << tokens[counter - 1].token <<">"<< endl;
			}
			else if (PTb[nti][tokenNo] == -997) // if Skip Occur
			{
				parserErrors << "<" << tokens[counter - 1].type << "," << tokens[counter - 1].token << ">" << endl;
				flag = true;
			}
			if (st.isEmpty() && counter < tokenCounter)
			{
				st.push(0);
			}
		}
	}
	delete[] arr;
}
Parser::~Parser()
{
	tokenFile.close();
	delete[] Terminals;
	delete[] nonTerminals;
	for (int i = 0; i < NoOfNTerms; i++)
	{
		delete[] PTb[i];
	}
	for (int i = 0; i < NoOfProds; i++)
	{
		delete[] cfg[i];
	}
	parserErrors.close();
}
