#ifndef PARSERAST_h
#define PARSERAST_h

#include <string> //because lexer will work with std::string
#include <vector> //imports the vector

//this says that the parser function will take a vector of strings, and return a vector of strings.
std::vector < std::string > parserast(std::vector < std::string > inputFunction); 

#endif