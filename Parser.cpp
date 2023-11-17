#include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include "TokenType.h"
#include "Token.h"
#include <ctype.h>
#include <map>
using namespace std;

class Parser {
    private:
        vector<Token> tokens;
        int current = 0;

    Parser(vector<Token> tokens) {
    this->tokens = tokens;
    }
    
    shared_ptr<Expr> expression(){
        return equality();
    }
    shared_ptr<Stmt> statement() {
    if (match(PRINT)) return printStatement();

    return expressionStatement();
  }
    shared_ptr<Stmt> printStatement() {
      shared_ptr<Expr> value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return Stmt::Print(value);
  }
   shared_ptr<Stmt> expressionStatement() {
      shared_ptr<Expr> expr = expression();
      consume(SEMICOLON, "Expect ';' after expression.");
      return new Stmt.Expression(expr);
  }
    vector<shared_ptr<Stmt>> Parse(){
        vector<shared_ptr<Stmt>> statements;
        while(!isAtEnd()){
          statement.emplace_back(declaration());
        }
    }
    shared_ptr<Stmt> declaration() {
    try {
      if (match(VAR)) return varDeclaration();

      return statement();
    } catch (ParseError error) {
      synchronize();
      return nullptr;
    }
  }
    shared_ptr<Stmt> varDeclaration() {
      Token name = consume(IDENTIFIER, "Expect variable name.");

      shared_ptr<Expr> initializer = nullptr;
      if (match(EQUAL)) {
        initializer = expression();
    }

      consume(SEMICOLON, "Expect ';' after variable declaration.");
      return shared_ptr<Var>(move(name), initializer);
  } 

    
    shared_ptr<Expr> equality() {
        Expr expr = comparison();

        while (match(BANG_EQUAL, EQUAL_EQUAL)) {
            Token operator = previous();
            shared_ptr<Expr> right = comparison();
            expr = shared_ptr<Binary>(expr, move(operator), right);
    }

    return expr;
  }
    shared_ptr<Expr> comparison() {
    shared_ptrExpr expr = term();

    while (match(TokenType::GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
      Token operator = previous();
      shared_ptr<Expr> right = term();
      expr = new Expr.Binary(expr, move(operator), right);
    }

    return expr;
  }
    shared_ptr<Expr> term() {
        shared_ptr<Expr> expr = factor();

        while (match(MINUS, PLUS)) {
            Token operator = previous();
            Expr right = factor();
            expr = shared_ptr<Binary>(expr, move(operator), right);
    }

    return expr;
  }
    shared_ptr<Expr> factor() {
        shared_ptr<Expr> expr = Unary();

    while (match(SLASH, STAR)) {
        Token operator = previous();
        shared_ptr<Expr> right = unary();
        expr = shared_ptr<Binary>(expr, move(operator), right);
    }

    return expr;
  }
    shared_ptr<Expr> unary() {
    if (match(BANG, MINUS)) {
      Token operator = previous();
      shared_ptr<Expr> right = unary();
      return shared_ptr<Unary>(move(operator), right);
    }

    return primary();
  }
    shared_ptr<Expr> primary() {
        if (match(FALSE)) return shared_ptr<Literal>(false);
        if (match(TRUE)) return shared_ptr<Literal>(true);
        if (match(NIL)) return shared_ptr<Literal>(NULL);

        if (match(NUMBER, STRING)) {
        return shared_ptr<Literal>(previous().literal);
    }
        if (match(IDENTIFIER)) {
          return shared_ptr<Var>(previous());
      }

        if (match(LEFT_PAREN)) {
            Expr expr = expression();
            consume(RIGHT_PAREN, "Expect ')' after expression.");
            return shared_ptr<Grouping>(expr);
    }
  }

    bool match(initializer_list<TokenType> types) {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
      }
    }
    Token consume(TokenType type, string message) {
        if(check(type)) return advance();

        throw error(peek(), message);
  }

    return false;
  }
    bool check(TokenType type) {
        if (isAtEnd()) return false;
        return peek().type == type;
  }
    Token advance() {
        if (!isAtEnd()) current++;
        return previous();
  }
    bool isAtEnd() {
    return peek().type == EOF;
  }

    Token peek() {
    return tokens.at(current);
  }

    Token previous() {
    return tokens.at(current - 1);
  }
    ParseError error(Token token, string message) {
        throw error(token, message);

  }
    void synchronize() {
        advance();

        while (!isAtEnd()) {
            if (previous().type == SEMICOLON) return;

            switch (peek().type) {
                case CLASS:
                case FUN:
                case VAR:
                case FOR:
                case IF:
                case WHILE:
                case PRINT:
                case RETURN:
                return;
            }

            advance();
        }
    }
    
};
