# include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int start = 0;
int current = 0;
int line = 1;

class Scanner{
	public:
		void scanTokens();
	private:
		string source;
		vector<Token> tokens;
		int start = 0;
		int current = 0;
		int line = 1;

		IsAtEnd();
		scanToken();
		advance();
		addToken();

		
		


};

bool Scanner::IsAtEnd(){
	return current >= source.size();
}

vector<Token> Scanner::scanTokens(){
	while(!IsAtEnd()){
		start = current
		scanTokens();
	}

	tokens.push_back(EOF,"",null,line);
	return tokens;
}

void scanToken(){
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
		
			
	}
}
char Scanner::advance() {
    return source.charAt(current++);
  }

void Scanner::addToken(TokenType type) {
    addToken(type, null);
  }

void Scanner::addToken(TokenType type, Object literal) {
    String text = source.substring(start, current);
    tokens.add(new Token(type, text, literal, line));
  }



