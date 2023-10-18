#include <iostream>
#include <string>
#include <any>
#include "TokenType.h"
using namespace std;


class Token{
private:
	TokenType	ttpye;	
	string		lexeme;
	std::any	literal;
	int			line;

	};




