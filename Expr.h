
#include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include "TokenType.h"
#include "Token.h"
#include "interpreter.cpp"
#include <ctype.h>
#include <map>
using namespace std;

class Expr { 
  static class Binary extends Expr {
    Binary(Expr left, Token operator, Expr right) {
      this->left = left;
      this->operator = operator;
      this->right = right;
    }

    Expr left;
    Token operator;
    Expr right;
  }

};