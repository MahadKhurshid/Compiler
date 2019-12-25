#include"lexical.h"

lexical::lexical()
{
	//	Constructor is responsible for all the loading data into memory
	fin.open("ioFiles/input.txt", ios::in);
	foutTokens.open("ioFiles/tokens.csv", ios::out);
	foutError.open("ioFiles/lexicalErrors.csv", ios::out);
	lexicalErrors = 0;
	tempBuffer = NULL;
	bufferCount = 0;
	buffer = new char[MAXSIZE + MAXSIZE];
	memset(buffer, 0, sizeof(buffer[0]) * (MAXSIZE + MAXSIZE));
	counter = 0;
	symbolTable = nullptr;
	loadCode();
	loadTransTable();
	loadTransColumns();
	loadMap();
	loadAcceptingStates();
	loadToken_Types();
	loadKeywords();
}
lexical::lexical(Table *table)
{
	symbolTable = table;
	//	Constructor is responsible for all the loading data into memory
	fin.open("ioFiles/input.txt", ios::in);
	foutTokens.open("ioFiles/tokens.csv", ios::out);
	foutError.open("ioFiles/lexicalErrors.csv", ios::out);
	lexicalErrors = 0;
	tempBuffer = NULL;
	bufferCount = 0;
	buffer = new char[MAXSIZE + MAXSIZE];
	memset(buffer, 0, sizeof(buffer[0]) * (MAXSIZE+MAXSIZE));
	counter = 0;
	loadCode();
	loadTransTable();
	loadTransColumns();
	loadMap();
	loadAcceptingStates();
	loadToken_Types();
	loadKeywords();
}
lexical::~lexical()
{
	fin.close();
	foutError.close();
	foutTokens.close();
	delete[] buffer;
}
// these functions used for loading files into memory
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool lexical::loadCode()
{
	string str;
	buffer[0] = '\0';
    bufferCount = -1;
	counter = 0;
    bool flag = false;
    if(tempBuffer != NULL)
    {
        strcat_s(buffer, MAXSIZE,tempBuffer);
        bufferCount += strlen(tempBuffer);
        delete[] tempBuffer;
        tempBuffer = NULL;
    }
    while (!fin.eof() && bufferCount < MAXSIZE + MAXSIZE)
    {
        getline(fin, str);
		if((str.length() + bufferCount)+2 >= MAXSIZE + MAXSIZE)
        {
            tempBuffer = new char[MAXSIZE];
			tempBuffer[0] = '\0';
            strcat_s(tempBuffer, MAXSIZE, str.c_str());
			tempBuffer[str.length()] = '\n';
			tempBuffer[str.length()+1] = '\0';
            break;
        }
        strcat_s(buffer, MAXSIZE + MAXSIZE, str.c_str());
        bufferCount += str.length()+1;
        if (fin.eof() && bufferCount == -1)
        {
            bufferCount++;
            flag = true;
        }
        buffer[bufferCount] = '\n';
		buffer[bufferCount+1] = '\0';
    }
	if (fin.eof() && bufferCount == -1)
	{
		bufferCount++;
		flag = true;
	}
    return flag;
}
char lexical::getChar()
{
    if(counter >= bufferCount)
    {
        if(loadCode())
            return '\0';
    }
    return buffer[counter++];
}
void lexical::loadTransTable()
{
    ifstream file;
    file.open("ioFiles/transTable.csv", ios::in);
    string str;
    for(int i=0; i<STATES; i++)
    {
        getline(file, str);  
        stringstream lineStream(str); 
        int j = 0;
        for (j = 0; j < TRANS_TOKENS_TYPE; j++)
        {   
            str.clear();
            getline(lineStream, str, ',');
            stringstream tempstream(str);
            tempstream>>mapping[i][j];
            //printf("(%d), ", map[i][j]);
        }
        getline(lineStream, str);
        stringstream tempstream(str);
        tempstream>>mapping[i][j];
        //printf("(%d)\n", map[i][j]);
    }
    file.close();
}
void lexical::loadTransColumns()
{
	ifstream file;
	file.open("ioFiles/transColumns.csv", ios::in);
	int index = 0;
	while (!file.eof())
	{
		file >> mappingColumns[index];
		index++;
	}
	file.close();
}
void lexical::loadMap()
{
	ifstream file;
	file.open("ioFiles/transMap.csv", ios::in);
	int index = 0;
	while (!file.eof())
	{
		file >> map[index];
		index++;
	}
	file.close();
} 
void lexical::loadAcceptingStates()
{
	ifstream file;
	file.open("ioFiles/AcceptingStates.csv", ios::in);
	int index = 0;
	while (!file.eof())
	{
		file >> accStates[index];
		index++;
	}
	file.close();
}
void lexical::loadToken_Types()
{
	token_type[0] = ""; // there would be nothing in 0th index;
	ifstream file;
	file.open("ioFiles/token_type.csv", ios::in);
	int index = 1;
	while (!file.eof())
	{
		getline(file, token_type[index]);
		index++;
	}
	file.close();
}
void lexical::loadKeywords()
{
	for (int i = 29; i < 89; i++)
	{
		if(keywords[token_type[i].length()] != "")
			keywords[token_type[i].length()] += " ";
		keywords[token_type[i].length()] += to_string(i);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
string lexical::checkIfKeyword(string str)
{
	//	Hash Function on average of O(n/2)
	stringstream s(keywords[str.length()]);
	int value;
	while(s>>value)
	{
		if (!strcmp(str.c_str(), token_type[value].c_str()))
		{
			return token_type[value].c_str();
		}
	}
	return "";
}
int lexical::getNoOfLexicalErrors()
{
	return lexicalErrors;
}
void lexical::makeToken(string value, int token_t)
{
	if (token_t < 0)
	{
		// if token type is negative means we have to decrement
		// and change the token to positive to read the token type
		token_t = token_t * (-1);
		counter--;
	}

	foutTokens << token_type[token_t] << "," << value<<endl;
	//cout << token_type[token_t] << "," << value << endl;
	if (symbolTable != nullptr) {
		char *str = new char[20];
		strcpy_s(str, 20, value.c_str());
		symbolTable->lookupInsert(str);
		delete[] str;
	}
}
void lexical::ifErrorCame(string token, bool &flag, char ch)
{
	//	if error came
	if (token == "input")
	{
		//	check!, it might input-> keyword
		counter--;
		token += getChar();
		token += getChar();
		counter++;
		if (token != "input->")
		{
			counter--; counter--;
		}
	}
	if (token == "output")
	{
		//	check!, it might output<- keyword
		counter--;
		token += getChar();
		token += getChar();
		counter++;
		if (token != "output<-")
		{
			counter--; counter--;
		}
	}
	string value = checkIfKeyword(token);
	if (value != "")
	{
		// means it's an keyword
		flag = false;
		foutTokens << "keyword" << "," << value << endl;
		
		if(symbolTable != nullptr){ 
			char *str = new char[20];
			strcpy_s(str, 20, value.c_str());
			symbolTable->lookupInsert(str);
			delete[] str;
		}
		counter--;
		return;
	}
	if (token.length() == 0)
	{
		// if token is empty means our input exists in ch
		token += ch; counter++;
	}
	foutError << token << ", ERROR" << endl;
	//cout << token << ", ERROR" << endl;
	lexicalErrors++;
	flag = false;
	token.clear();
	counter--;
	return;
}
void lexical::runLexicalAnalyser()
{
	char ch;
	int cstate = 0, prevstate = 0;
	string token;
	while (true) // 1st
	{
		// Get Single character from Buffer
		ch = getChar();
		if (ch == '\0') break;
		if (ch == ' ' || ch == '\n' || ch == '\t') continue;
		cstate = 0;
		bool flag = true;
		token.clear();
		while (!accStates[cstate])	// 2nd
		{
			// store previous state in case of future use
			prevstate = cstate;
			// Get Next State
			cstate = mapping[cstate][map[ch]];	// 3rd
			//	Check if Exponent
			if ((ch == 'e' || ch == 'E') && token.length()>0 && token[token.length() - 1] >= '0' && token[token.length() - 1] <= '9')
			{
				cstate = mapping[prevstate][22];
			}
			if (ch == ';' && token.length()<=0)
			{
				foutTokens << ";" << "," << ";" << endl;
				flag = false;
				break;
			}
			if (cstate == -1)
			{
				// this tells Error State Occur 
				ifErrorCame(token, flag, ch);
				break;
			}
			if (ch == '\0')	break;
			if (ch != ' ' && accStates[cstate] > 0) token += ch;
			if (!accStates[cstate])	//	4th
			{
				//if current state doesn't reach accepting state yet
				token += ch;
				ch = getChar();	//	5th
				flag = true;
			}
		}
		if (flag)
		{
			//	Make token
			makeToken(token, accStates[cstate]);	//	6th
			if (ch == '\n') counter++;
		}
	}
}