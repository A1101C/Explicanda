//this is the parser-ast, used to parse the tokens and organize them into a tree to be evaluated

#include <iostream> //required for any basic input/output operations
#include <cctype> //needed for isalpha
#include <string> //imports the string library
#include <vector> //imports the vector
#include "config.h" //includes the config file containing debug variables
#include "utils.h" //this has the containsSubstring function

//start of a basic attempt to organize the tokens based on PEMDAS
std::vector < std::string > pemdas(std::vector<std::string> inputVector, int operatorCount) {
    std::vector < std::string > calcVector; //creates the vector where the correctly ordered functions and their calculations will be kept.
    for (int n = 0; n < operatorCount; ++n) { //for the number of operators we have
        for (int i = 0; i < inputVector.size(); ++i) {//look at every position in the input vector
            if (inputVector[i] == "(") { //if i is (
                calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator
                calcVector.push_back(inputVector[i]); //add it to the top of its branch
                while (inputVector[i]!= ")") {
                    if (inputVector[i] == "^") { //if i is a ^
                        calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                        calcVector.push_back(inputVector[i]); //add it to the back of the seat
                    }
                    else if (inputVector[i] == "*" || inputVector[i] == "/") { //if i is a * or /
                        calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                        calcVector.push_back(inputVector[i]); //add it to the back of the ast
                    }
                    else if (inputVector[i] == "+" || inputVector[i] == "-") { //if i is a + or -
                        calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                        calcVector.push_back(inputVector[i]); //add it to the back of the ast
                    }
                }
            }
            if (inputVector[i] == "^") { //if i is a ^
                calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                calcVector.push_back(inputVector[i]); //add it to the back of the seat
            }
            else if (inputVector[i] == "*" || inputVector[i] == "/") { //if i is a * or /
                calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                calcVector.push_back(inputVector[i]); //add it to the back of the ast
            }
            else if (inputVector[i] == "+" || inputVector[i] == "-") { //if i is a + or -
                calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                calcVector.push_back(inputVector[i]); //add it to the back of the ast
            }
        }
    }
    return calcVector;
}


//Begining of the parser and AST builder
std::vector < std::string > parserast(std::vector < std::string > inputVector) {

    std::vector < std::string > outputVector;

    if (config::debugMode) { //prints the inputVector for the cleaner to the console if debug is true
        std::cout << "AST started with tokens:   ";
        for (const std::string& token : inputVector) {
            std::cout << "[" << token << "], ";
                }
        std::cout << std::endl;
    }

    std::vector < std::string > calcVector; //creates the vector where the correctly ordered functions and their calculations will be kept.
    
    /* for every position check for the operators from lowest to highest precedence. when one is found put the operator in Branch(1) then the fuctions to the left and right in leaf(1), 
    then find the next operator and put it in branch(2) and the values to the left and right in leaf(2), then keep going.
    */

    std::vector < std::string > operators = {"(", ")", "^", "*", "/", "+", "-", "="}; //makes a vector to hold operators
    int operatorCount = 0; //initializes a variable to keep track of the count of operators

    for (int n = 0; n < inputVector.size(); ++n) { //this loop will check every position in the inputVector
         std::string currentToken(inputVector[n]); //make it equal to the first character of the next string in vector position n
            if (containsSubstring(currentToken, operators)) { //check if the current token is an operator
                operatorCount += 1; //increase the operator count by 1
        }
    }

    calcVector = pemdas(inputVector, operatorCount);

    if (config::debugMode) { //prints the inputFunction for the cleaner to the console if debug is true
        std::cout << "Parser AST Finished with token order:   ";
        for (const std::string& token : calcVector) {
            std::cout << "[" << token << "], ";
        }
        std::cout << std::endl;
    }
    
    return calcVector;
}