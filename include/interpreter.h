#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string> //because lexer will work with std::string
#include <vector> //imports the vector

//this says that the parser function will take a vector of strings, and return a double
double interpreter(std::vector < std::string > inputFunction); 

#endif