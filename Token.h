#include <iostream>
#include <string>
#include <any>
#include "TokenType.h"
using namespace std;


class Token{
public:
	TokenType	type;	
	string		lexeme;
	std::any	literal;
	int			line;

	Token(TokenType ttype, string llexeme, std::any lliteral, int lline){
		type = ttype;
		lexeme = llexeme;
		literal = lliteral;
		line = lline;
	}
	};




