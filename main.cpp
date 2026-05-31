//This is the main entry point of the function

#include <iostream> //required for any basic input/output operations
#include <cctype> //needed for isalpha
#include <string> //imports the string library
#include <vector> //imports the vector
#include <cstdlib>   //imports atof to convert a string to a double

#include "config.h" //includes the config file containing debug variables
#include "cleaner.h" //includes the cleaner.h which defines the cleaner function in cleaner.cpp
#include "lexer.h" //includes the lexer.h file defining the lexer
#include "parserast.h" //includes the parser and ast file
#include "interpreter.h" //includes the interpreter.h file defining the interpreter

int main(int argCount, char*argVector[]) {    //this is the main fuction, int means that it will return an int value to whatever ran it, 0 means success and 1 means failure
//arg count is the number of arguments going in, argString is the actual user input function

    if (argCount < 2) {
        std::cerr << "{\"error\": \"No expression provided. Usage: ./engine [expr] or ./engine [expr] [minX] [maxX] [step]\"}\n";
        return 1; //exit safely instead of trying to read empty arguments
    }

    std::string messyFunction = argVector[1]; //defines the messy expression as the first argument for the input passed by the api

    //safely preload variables for when only graphing
    double xMin = 0.0;
    double xMax = 0.0;
    double xSteps = 0.0;

    //load the actual variables if they exist
    if (argCount >= 5) {
        double xMin = std::atof(argVector[2]); //states the xMin is the second input
        double xMax = std::atof(argVector[3]); //states the xMax is the third input
        double xSteps = std::atof(argVector[4]); //states the xSteps is the fourth input
    }


    std::string cleanFunction = cleaner(messyFunction); //declares a string variable to hold a cleaned up input and gets the cleanFunction by passing the messy function to the cleaner
    std::vector < std::string > tokenizedFunction = lexer(cleanFunction); //declares a vector of string variables to hold the tokens for the input and gets the tokens by passing the function to the lexer
    std::vector < std::string > parsedFunction= parserast(tokenizedFunction); //declares a vector of string variables to hold a cleaned up input and parses the function by passing the tokens to the parser
    double solution = interpreter(parsedFunction); //declares a double to hold the solution and solves the expresion by passing the parsed tokens to the interpreter


    if (config::debugMode) { //prints the messy function and clean function if debug mode is true
        std::cout << messyFunction << "    Cleaned to:    " << cleanFunction << " \n";
        std::cout << "Tokenized to:  "; //prints each token inside brackets for our tokenized vector
        for (const std::string& token : tokenizedFunction) {
            std::cout << "[" << token << "], ";
        }
        std::cout << std::endl;
        std::cout << "Parsed to:  "; //prints each token inside brackets for the parsed vector
        for (const std::string& token : parsedFunction) {
            std::cout << "[" << token << "], ";
        }
        std::cout << std::endl;
        std::cout << "solution is: "<< solution << " \n";
    }
    
    std::cout << solution << std::endl;
    return 0;
}
