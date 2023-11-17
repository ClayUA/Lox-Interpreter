#include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include "TokenType.h"
#include "Token.h"
#include <ctype.h>
#include <map>
using namespace std;




class RuntimeError{
  Token token;

  RuntimeError(Token& token, string message) {
    runtime_error(message);
    this->token = token;
  }
}