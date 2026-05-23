#ifndef PARSER-AST_h
#define PARSER-AST_h

#include <string> //because lexer will work with std::string
#include <vector> //imports the vector

//this says that the parser function will take a vector of strings, and return a vector of strings.
std::vector < std::string > parser-ast(std::vector < std::string > inputFunction); 

#endif