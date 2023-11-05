# include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include <TokenType.h>
#include <Token.h>
#include <ctype.h>
#include <map>
using namespace std;



class Scanner{
	public:
		vector<Token> scanTokens();
		Scanner(string source);
	private:
		string source;
		vector<Token> tokens;
		int start = 0;
		int current = 0;
		int line = 1;

		bool IsAtEnd();
		void scanToken();
		char advance();
		void addToken(TokenType type, std::any literal);
		void addToken(TokenType ttype);
		bool match(char expected);
		char peek();
		void String();
		void number();
		bool IsDigit(char c);
		char peekNext();
		void identifier();

		map<string, TokenType> keywords;
		
		
		


};

Scanner::Scanner(string source){
	keywords = {
			 	{"and",    AND},
    			{"class",  CLASS},
    			{"else",   ELSE},
    			{"false",  FALSE},
    			{"for",    FOR},
    			{"fun",    FUN},
    			{"if",     IF},
    			{"nil",    NIL},
    			{"or",     OR},
    			{"print",  PRINT},
    			{"return", RETURN},
    			{"super",  SUPER},
    			{"this",   THIS},
    			{"true",   TRUE},
    			{"var",    VAR},
    			{"while",  WHILE},
		};
}

bool Scanner::IsAtEnd(){
	return current >= source.size();
}

vector<Token> Scanner::scanTokens(){
	while(!IsAtEnd()){
		start = current;
		scanToken();
	}

	tokens.emplace_back(Token(TokenEOF,"",NULL,line));
	return tokens;
}

void Scanner::scanToken(){
	char c = advance();
	switch(c){
		case '(': addToken(LEFT_PAREN); break;
    	case ')': addToken(RIGHT_PAREN); break;
    	case '{': addToken(LEFT_BRACE); break;
    	case '}': addToken(RIGHT_BRACE); break;
    	case ',': addToken(COMMA); break;
    	case '.': addToken(DOT); break;
    	case '-': addToken(MINUS); break;
    	case '+': addToken(PLUS); break;
    	case ';': addToken(SEMICOLON); break;
    	case '*': addToken(STAR); break;
		case '!':
			addToken(match('=') ? BANG_EQUAL : BANG);
			break;
		case '=':
			addToken(match('=') ? EQUAL_EQUAL: EQUAL);
			break;
		case '<':
			addToken(match('=') ? LESS_EQUAL: LESS);
			break;
		case '>':
			addToken(match('=') ? GREATER_EQUAL: GREATER);
			break;
		case '/':
			if(match('/')){
				while(peek() != '\n' && !IsAtEnd()) advance();
			}
			else{
				addToken(SLASH);
			}
			break;

		case ' ':
		case '\r':
		case '\t':
			break;

		case '\n':
			line++;
			break;

		case '"':
			string();
			break;


		default:
			if(isdigit(c)){
				number();
			}
			else if(isalpha(c)){
				identifier();
				
			}
			else{
			runtime_error{"Unexpected Character"};
			break;
			}
	
		
	}
}

bool Scanner::match(char expected){
	if(IsAtEnd()){
		return false;
	if(source[current] != expected){
		return false;
	}

	current++;
	return true;
	}
}
char Scanner::peek(){
	if(IsAtEnd()) return '\0';
	return source[current];

}
char Scanner::advance() {
    return source.at(current++);
  }

void Scanner::addToken(TokenType ttype) {
    addToken(ttype, NULL);
  }

void Scanner::addToken(TokenType type, std::any literal) {
    string text = source.substr(start, current - start);
    tokens.emplace_back(Token(type, text, literal, line));
  }

void Scanner::String(){
	while (peek() != '"' && !IsAtEnd()) {
      if (peek() == '\n') line++;
      advance();
	}
}
void Scanner::number(){
	while (isdigit(peek())){
		advance();
	}
    if (peek() == '.' && isdigit(peekNext())) {
      advance();
      while (isdigit(peek())){
		 advance();
	  }
    }
    addToken(NUMBER,stod(source.substr(start, current - start)));
	if(IsAtEnd()){
		runtime_error{"Undending String"};
		return;
	}
	advance();


	string value = source.substr(start, current - start);
	addToken(STRING,value);
}

void Scanner::identifier(){
    while (isdigit(peek()) || isalpha(peek()) || peek() == '_') {
        advance();
    }
	string text = source.substr(start, current - start);
	TokenType toke = keywords[text];
	if(toke == NULL) toke = IDENTIFIER;
	addToken(toke);
}

char Scanner::peekNext(){
	if (current + 1 >= source.size()){
		return '\0';
	}
	return source[current + 1];
}




