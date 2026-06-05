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
#include "graphpoints.h" //includes the graphing function

int main(int argCount, char*argVector[]) {    //this is the main fuction, int means that it will return an int value to whatever ran it, 0 means success and 1 means failure
//arg count is the number of arguments going in, argVector is the actual user input function
//the main counts as an argument so it is argVector[0], so a regular expression being solved will have 2 args

    double solution; //initializes solution as a double

    if (argCount < 1) {
        std::cerr << "{\"error\": \"No expression provided. Usage: ./engine [expr] or ./engine [expr] [minX] [maxX] [xCount]\"}\n";
        return 1; //exit safely instead of trying to read empty arguments
    }

    std::string messyFunction = argVector[1]; //defines the messy expression as the first argument for the input passed by the api

    //safely preload variables for when not graphing
    double xMin = 0.0;
    double xMax = 0.0;
    double xCount = 0.0;

    //run the function through the cleaner, lexer, and parser regardless of if we are graphing or not
    std::string cleanFunction = cleaner(messyFunction); //declares a string variable to hold a cleaned up input and gets the cleanFunction by passing the messy function to the cleaner
    std::vector < std::string > tokenizedFunction = lexer(cleanFunction); //declares a vector of string variables to hold the tokens for the input and gets the tokens by passing the function to the lexer
    std::vector < std::string > parsedFunction= parserast(tokenizedFunction); //declares a vector of string variables to hold a cleaned up input and parses the function by passing the tokens to the parser

    // if we dont have all 5 arguments and it doesn't contain x then simply solve the expression
    bool containsX = false; //initializes the bool

    if (containsString("x", parsedFunction) == true){ //checks if the string contains an x
        bool containsX = true; //if it does then it sets the variable to true
    }

    if (argCount < 4 && !containsX) { 
        solution = interpreter(parsedFunction); //solves the expresion by passing the parsed tokens to the interpreter
        std::cout << solution << std::endl; //if we can just solve it then print/return it to the
    }

    //if we do have all 5 arguments then we can calculate values for our graph, to start I will make it generate a vector of values within our xMin and xMax, then calculate the solution for each x value
    //I want to be able to play with the step size between x values to see how long it takes to calculate a large number of values
    if (argCount >= 4) {
        
        //load the actual variables if they exist
        double xMin = std::stod(argVector[2]); //states the xMin is the second input
        double xMax = std::stod(argVector[3]); //states the xMax is the third input
        double xCount = std::stod(argVector[4]); //states the xCount is the fourth input

        std::vector < std::pair < double, double >> xyPairs; //initializes a vector of pairs to hold xy values

        xyPairs = graphpoints(parsedFunction, xMin, xMax, xCount); //passes the parsedFunction into the graphpoints tool

        for (int n = 0; n < xyPairs.size(); n++ ) { //for every pair in the xyPairs vector
            std::cout << "(" << xyPairs[n].first << ", " << xyPairs[n].second << ")" << " \n"; //prints each pair as xValue, yValue
        }

        std::vector < std::pair < double, double >> yInt; //initializes a vector of pairs to hold the yInt
        yInt = graphpoints(parsedFunction, 0.0, 1.0, 1.0);
        solution = yInt[0].second;
    }

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
    
    return 0;
}
