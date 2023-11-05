#include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include <TokenType.h>
#include <Token.h>
#include <ctype.h>
#include <map>
#include <string_view>
using namespace std;



int main(int argc, char* argv[]){
    if(argc != 1){
        cout << "usage: generate_ast <output directory>" <<;
        exit(64);
    }
    string outputDir = argv[0];
    defineAST(outputDir, "Expr", {
        "Binary   : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token operator, Expr right",
    });
}

void defineAST(string outputDir, string basename, vector<string> types){
    string path = outputDir + "/" + basename + ".h";
    ofstream writer{path};
    writer = << "#pragma once\n"
            "\n"
            "#include <any>\n"
            "#include <memory>\n"
            "#include <utility>"
            "#include <vector>\n"
            "#include \"Token.h\"\n"
            "\n";
    for (string type : types){
        string classname = trim(split(type, ": ")[0]);
        string fields = trim(split(type, ": ")[1]);
        defineType(writer, basename, classname, fields);
    }

}

void defineType