Compiler - by Harry

i hope you can understand and learn from my hardwork!

In Compiler following things includes:
	->	Lexical
	->	Parser
	->	Input Output Files as iofiles
	->	Stack
	->	Symbol table (Tabl includes Symbol Variables)
	-> 	Driver Code

+) LEXICAL:
	
	Lexical is Class Which have following functionailities:
	
	   Provide code as input in iofiles/input.txt 
	1) load code from iofiles/input.txt into buffer and if buffer is full but file is not end
	   it will stop the loading. Left data will be load until loaded data not used!
	   (buffer Counter will use to maintain the character position)
	2) DFAs loaded in program as Transition table.
	3) When lexical will run 2 files will be created iofiles/lexicalErrors.txt which inlcudes
	   all the errors detected by lexical and iofiles/tokens.csv which inlcudes all the tokens
	   made from input you provide according to DFA's.
	   - AcceptingStates.csv // all the final states in DFAs are stored in it.
	   - token_type.csv // token types which DFA exists are stored in it.
	   - transColumns.csv // all the coloumns of transition table are stored in it.
	4) you can check all the leftover functionailities according to the knowledge u get 
	   and by Code Provided.

+) Parser:
	
	Parser is Class Which have following functionailities:
	
	   Tokens are in iofiles/tokens.csv
	1) load tokens from iofiles/tokens.csv into structure and if structure is full but 
	   file is not end it will stop the loading. Left data will be load until loaded 
           data not used!
	   (token Counter will use to maintain the token position)
	2) cfg loaded in program in numbers according to terminal and non-terminal array.
	   eg: 
		- Id,rate1 // token
		in stack first load the first non-terminal which is 0
		then search the token in parse table, is there is Id token exist in CFG
		- it will go to the rule mentioned in parse table:
			parsetable[non-terminal][tokenNo] = Rule Number
		- cfg[rule Number] // if it cfg have identifier then rate1 will be parsed.
		- iofiles/cfg.txt
		// cfg stored in it like:
		//	Function -> Type identifier (ArgList) CompoundStmt
		//	5 -3 -9 1 -10 16 -999
		//	5 means "Type" according to non-terminals array
		//	-3 means "identifier" according to terminals array
		//	-9 means "(" according to terminals array 
		//	1 means "ArgList" according to non-terminals array 
		// 	so on.
	3) When Parser will run a file will be created iofiles/parserErrors.txt which inlcudes
	   all the errors detected by parser.
	4) you can check all the leftover functionailities according to the knowledge u get 
	   and by Code Provided.
