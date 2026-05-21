//this is the lexer, used to parse the cleaned string into a series of single token strings

#include <iostream> //required for any basic input/output operations
#include <string> //imports the string library
#include <vector> //imports the vector
#include "config.h" //includes the config file containing debug variables

//Begining of the lexer function
std::vector < std::string > lexer(std::string inputFunction) {

    if (config::debugMode) { //prints the inputFunction for the lexer to the console if debug is true
        std::cout << "Lexer started with string inputFunction:   " << inputFunction << std::endl;
    }

    std::vector < std::string > lexedTokens; //initializes the vector to hold the tokens

    std::string currentToken; //creates a string to hold the token currently being assembled

    std::vector < std::string > operators = {"(", ")", "^", "*", "/", "+", "-", "="}; //makes a vector to hold operators
    std::vector < std::string > trigFunctions = {"sin", "cos", "tan", "sec", "csc", "cot"}; //a vector holding trig functions
    std::vector < std::string > logFunctions = {"log", "ln", "e"}; //a vector to hold log, ln, and e. 



    int tokenCount = 1; // initializes a variable to keep track of how many tokens there are

    for (int n = 0; n < inputFunction.length(); ++ n) { //for every position in the input function
        char currentChar = inputFunction[n]; //the current character is in the n position

        if (isdigit(currentChar)) { //if currentChar is a digit
            currentToken.push_back(currentChar); //add it to the current token
            while (n + 1 < inputFunction.length() && isdigit(inputFunction[n + 1])){ //and as long as the next char is also a number
                n++; //this moves n to the next position if it exists and is a digit
                currentToken.push_back(inputFunction[n]); //add it to the end of the current token
            }
            lexedTokens.push_back(currentToken); //add the entire token we just made to the vector
            currentToken.clear(); //now clear the token so that we can collect another one
        }

        //now find out if the next character is an operator
        
    }

    if (config::debugMode) { //prints the inputFunction for the cleaner to the console if debug is true
        std::cout << "Lexer Finished with tokens:   ";
        for (const std::string& token : lexedTokens) {
            std::cout << "[" << token << "], ";
                }
        std::cout << std::endl;
     }

    return lexedTokens;
}