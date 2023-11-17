#include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include "TokenType.h"
#include "Token.h"
#include "interpreter.cpp"
#include "Parser.cpp"
#include <ctype.h>
#include <map>
using namespace std;
class Lox {
    private:
        interpreter interpret = new interpreter();

};

void runtimeerror(RuntimeError error) {
        
}
void run(string source) {
  Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();
    Parser parser(tokens);
    vector<shared_ptr<Stmt>> statements = parser.parse();

  if (hadError) return;

  if (hadError) return;

  interpreter.interpret(statements);
}
void runPrompt() {
  while (1) {
    cout << "> ";
    string line;
    if (getline(cin, line)) break;
    run(line);
    hadError = false;
  }
}
int main(int argc, char* argv[]) {
    if (argc > 2) {
        cout << "Usage: jlox [script]" << endl;
        exit(64); 
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
  }
