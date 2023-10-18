# include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include <TokenType.h>
#include <Token.h>
using namespace std;



class Scanner{
	public:
		void scanTokens();
		Scanner(string source){
			this.source = source
		}
	private:
		string source;
		vector<Token> tokens;
		int start = 0;
		int current = 0;
		int line = 1;

		bool IsAtEnd();
		void scanToken();
		char advance();
		void addToken();
		bool match(char expected);

		
		


};

bool Scanner::IsAtEnd(){
	return current >= source.size();
}

vector<Token> Scanner::scanTokens(){
	while(!IsAtEnd()){
		start = current
		scanToken();
	}

	tokens.push_back(EOF,"",null,line);
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
				addToken(SLASH)
			}
			break;
		default:
			runtime_error{"Unexpected Character"};
			break;
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
    return source.charAt(current++);
  }

void Scanner::addToken(TokenType ttype) {
    addToken(ttype, null);
  }

void Scanner::addToken(TokenType type, std::any literal) {
    String text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
  }



