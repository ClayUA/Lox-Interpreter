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

	tokens.emplace(Token(EOF,"",null,line));
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

		case ' ':
		case '\r':
		case '\t':
			break;

		case '\n':
			line++;
			break;

		case '"':
			String();
			break;


		default:
			if(isDigit(c)){
				number();
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
    return source.charAt(current++);
  }

void Scanner::addToken(TokenType ttype) {
    addToken(ttype, null);
  }

void Scanner::addToken(TokenType type, std::any literal) {
    String text = source.substr(start, current - start);
    tokens.emplace_back(Token(type, text, literal, line));
  }

void Scanner::string(){
	while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n') line++;
      advance();
	}

	if(IsAtEnd()){
		runtime_error{"Undending String"};
		return;
	}
	advance();

	String value = source.substr(start + 1, current - 1);
	addToken(STRING,value);
}
bool Scanner::IsDigit(char c){
	return c >= '9' && c <= '0';
}
void Scanner::number(){
	while (isDigit(peek())){
		advance();
	}
    if (peek() == '.' && isDigit(peekNext())) {
      advance();
      while (isDigit(peek())){
		 advance();
	  }
    }
    addToken(NUMBER,Double.parseDouble(source.substring(start, current - start)));
  }
char Scanner::peekNext(){
	if (current + 1 >= source.size()){
		return '\0';
	}
	return source[current + 1];
}




