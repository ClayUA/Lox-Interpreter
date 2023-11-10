#include <algorithm>     
#include <cctype>         
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>      
#include <vector>
using namespace std;



int main(int argc, char* argv[]){
    if(argc != 1){
        cout << "usage: generate_ast <output directory>" <<;
        exit(64);
    }
    string outputDir = argv[0];
    defineAST(outputDir, 'Expr', {
        "Binary   : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token operator, Expr right",
    });
}
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
vector<string> split(const string& str, char delimiter) {
    vector<string> result;
    istringstream iss(str);
    string token;
    while (getline(iss, token, delimiter)) {
        result.push_back(trim(token));
    }
    return result;
}
void defineAST(string& outputDir, string& basename, vector<string> types){
    string path = outputDir + "/" + basename + ".h";
    ofstream writer{path};
    writer << "#pragma once\n"
            "\n"
            "#include <any>\n"
            "#include <memory>\n"
            "#include <utility>"
            "#include <vector>\n"
            "#include \"Token.h\"\n"
            "\n";
    for (string type : types){
        string classname = trim(split(type, ': ')[0]);
        writer << "struct " << classname << ";\n";
        }

        writer << "\n";
        defineVisitor(writer, basename, types);

          writer << "\n"
                    "struct " << basename << " {\n"
                    "  virtual std::any accept(" << basename <<
                    "Visitor& visitor) = 0;\n"
                    "};\n\n";
        for (string_view type : types) {
            string classname = trim(split(type, ': ')[0]);
            string fields = trim(split(type, ": ")[1]);
            defineType(writer, basename, classname, fields);
        }
}

void defineType(ofstream writer, string baseName,string className, string fieldList) {
    writer << "  static class " << className << " extends " <<
        baseName << "{" << endl;

    // Constructor.
    writer << "    " << className << "(" << fieldList << ")" << "{" << ;

    // Store parameters in fields.
     string fields = fieldList.split(', ');
    for (string field : fields) {
      string name = field.split(" ")[1];
      writer << "      this." << name << " = " << name << ";" << endl;
    }

    writer.println("    }");

    // Fields.
    writer.println();
    for (String field : fields) {
      writer.println("    final " + field + ";");
    }

    writer << "  }" << endl;
  }