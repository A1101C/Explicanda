//This is the main entry point of the function

#include <iostream> //required for any basic input/output operations
#include <cctype> //needed for isalpha
#include <string> //imports the string library
#include <vector> //imports the vector
#include "config.h" //includes the config file containing debug variables
#include "cleaner.h" //includes the cleaner.h which defines the cleaner function in cleaner.cpp
#include "lexer.h" //includes the lexer.h file defining the lexer
#include "parserast.h" //includes the parser and ast file
#include "interpreter.h" //includes the interpreter.h file defining the interpreter

int main() {    //this is the main fuction, int means that it will return an int value to whatever ran it, 0 means success and 1 means failure

    //Obtain the User Function to be Evaluated

    std::string messyFunction; //declares a string variable to hold the user's input
    std::cout << "Please enter the function or expression to be evaluated: "; //asks the user to input a function to be evaluated
    std::getline(std::cin, messyFunction); //gets the user's input and stores it in the variable messyFunction
    std::cout << "You entered: "; std::cout << messyFunction << std::endl; //outputs the user's input back to them

    std::string cleanFunction; //declares a string variable to hold a cleaned up input
    cleanFunction = cleaner(messyFunction);

    std::vector < std::string > tokenizedFunction;
    tokenizedFunction = lexer(cleanFunction);

    std::vector < std::string > parsedFunction;
    parsedFunction = parserast(tokenizedFunction);

    bool graphing = false;

    double solution;
    solution = interpreter(parsedFunction, graphing);

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

    //Determine the type of calculation to be preformed

    char userChoice; //initializes a character variable for the users choice

    std::cout << "What kind of Calculation should be preformed? \n" 
              << "(A)rithmetic such as +, -, *, \n"
              << "(G)raphing a function of x. \n"
              << "(C)AS, solving for x. \n"
              << "(D)erivative with respect to x. \n"
              << "(I)ntegrate with respect to x. \n"
              << "Enter a (N)ew function. \n"
              << "(Q)uit. \n"
              << "Choice: " << std::endl;
    std::cin >> userChoice; //gets the user's choice and stores it in the character variable userChoice

/*    switch (userChoice) {
        case 'A':
        case 'a':
        
    }*/

    return 0;
}
