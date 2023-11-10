# include <iostream>
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
    unique_ptr<Expr> expression(){
        return equality();
    }
    unique_ptr<Expr> equality() {
        Expr expr = comparison();

        while (match(BANG_EQUAL, EQUAL_EQUAL)) {
            Token operator = previous();
            unique_ptr<Expr> right = comparison();
            expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
  }
    unique_ptr<Expr> comparison() {
    unique_ptrExpr expr = term();

    while (match(TokenType::GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
      Token operator = previous();
      unique_ptrExpr right = term();
      expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
  }
    unique_ptr<Expr> term() {
        unique_ptr<Expr> expr = factor();

        while (match(MINUS, PLUS)) {
            Token operator = previous();
            Expr right = factor();
            expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
  }
    unique_ptr<Expr> factor() {
        unique_ptr<Expr> expr = unary();

    while (match(SLASH, STAR)) {
        Token operator = previous();
        unique_ptr<Expr> right = unary();
        expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
  }
    unique_ptr<Expr> unary() {
    if (match(BANG, MINUS)) {
      Token operator = previous();
      unique_ptr<Expr> right = unary();
      return make_shared<Expr::Unary>(operator, right);
    }

    return primary();
  }
    unique_ptr<Expr> primary() {
        if (match(FALSE)) return make_unique<Expr::Literal>(false);
        if (match(TRUE)) return make_unique<Expr::Literal>(true);
        if (match(NIL)) return make_unique<Expr::Literal>(NULL);

        if (match(NUMBER, STRING)) {
        return make_unique<Expr::Literal>(previous().literal);
    }

        if (match(LEFT_PAREN)) {
            Expr expr = expression();
            consume(RIGHT_PAREN, "Expect ')' after expression.");
            return make_shared<Expr::Grouping>(expr);
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
