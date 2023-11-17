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
    defineAST(outputDir, "Expr", {
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

    writer <<   "#pragma once\n"
                "#include <algorithm>\n"     
                "#include <cctype>\n"        
                "#include <fstream>\n"
                "#include <iostream>\n"
                "#include <sstream>\n"
                "#include <string>\n"
                "#include <string_view>\n"
                "#include <utility>\n"      
                "#include <vector>\n"
                " using namespace std;\n"
                "class " + basename + " {\n"

                defineVisitor(writer,basename,types);
                for (string type : types) {
                    string className = type.split(trim(":"))[0];
                    string fields = type.split(trim(":"))[1]; 
                    defineType(writer, baseName, className, fields);
                }
                "}";
                writer << "\n";
        }


void defineType(ofstream writer, string baseName,string className, string fieldList) {
    writer << "  class " << className << " extends " <<
        baseName << "{" << endl;

    // Constructor.
    writer << "    " << className << "(" << fieldList << ")" << "{" << ;

    // Store parameters in fields.
     string[] fields = fieldList.split(', ');
    for (string field : fields) {
      string name = field.split(" ")[1];
      writer << "      this->" << name << " = " << name << ";" << endl;
    }

    writer.println("    }");

    // Fields.
    writer << "\n";
    for (String field : fields) {
      writer << "    const " + field + ";\n";
    }

    writer << "  };" << endl;
  }
  void defineVisitor(){
      writer << "  interface Visitor<R> {";

    for (string type : types) {
        string typeName = type.split(trim(":"))[0];
        writer <<"    R visit" + typeName + baseName + "(" +
          typeName + " " + baseName.toLowerCase() + ");";
    }

    writer << "  }";

  }