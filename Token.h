#include <iostream>
#include <string>
#include <any>
#include "TokenType.h"
using namespace std;


class Token{
public:
	TokenType	type;	
	string		lexeme;
	any			literal;
	int			line;

	Token(TokenType ttype, string llexeme, any lliteral, int lline){
		this->type = ttype;
		this->lexeme = llexeme;
		this->literal = lliteral;
		this->line = lline;
	}
	};




