//this is the parser-ast, used to parse the tokens and organize them into a tree to be evaluated

#include <iostream> //required for any basic input/output operations
#include <cctype> //needed for isalpha
#include <string> //imports the string library
#include <vector> //imports the vector
#include <cctype> //used for isalnum
#include "config.h" //includes the config file containing debug variables
#include "utils.h" //this has the containsSubstring function

//start of a basic attempt to organize the tokens based on PEMDAS

/*while the number of operators 
    for the numper of positions
        if i = operator with highest to lowest priority
            if i was ( then we need to go through everything after I until we hit ) and add 1 to the main for loop for every operator contained in the ()
                organize the operators in the parenthesis and their values, 
                when we hit ) exit this loop and return to the for the number of operators loop
            if pos i is ) i is greater than 0 and i-1 is alphanumeric
                put pos i-1 in the calcvector  
            put pos i in the calcvector
            advance to the next priority operator

*/

std::vector < std::string > pemdas(std::vector<std::string> inputVector, int operatorCount) {
    std::vector < std::string > calcVector; //creates the vector where the correctly ordered functions and their calculations will be kept.
    std::string currentOperator; //a string to keep track of where we are in the function
    std::string currentPriority; //A string to determine the current highest priority operator
    int openParenthesis = 0
    std::vector < std::string > operators = {"(", ")", "^", "*", "/", "+", "-", "="}; //makes a vector to hold operators
    while (0 < operatorCount) { //while 0 is less than the operatorCount
        for (int i = 0; i < operators.size(); i++) { //look at every position in the operators vector
            currentPriority = operators[i]; //the current priority changes as we go down through the list to be sure we look at every possible operator in the right order
            for (int n = 0; n < inputVector.size(); n++ ) { //look at every position in the input vector
                currentOperator = inputVector[n]; //the current operator is in the nth position of the input function
                if (currentOperator == currentPriority && currentOperator == "(" ){ //and if the the current operator matches our priority and is an open parenthesis
                    if (0 < openParenthesis) { //if we have already had open parenthesis this must be an inset set of parenthesis
                        calcVector.insert(calcVector.begin(), inputVector[n]); //inset the inset parenthesis into the beginning of the function
                    }
                    openParenthesis += 1; //add one to the number of open parenthesis
                    if ( 0 < n){ //
                        calcVector.push_back(inputVector[n - 1]); 
                    }
                    calcVector.push_back(inputVector[n]);
                }
                else if ()
            }
        }
    }
    
    /*for (int i = 0; i < inputVector.size(); ++i) {//look at every position in the input vector
        if (inputVector[i] == "(") { //if i is (
            calcVector.push_back(inputVector[i]); //add it to the top of its branch
            if (config::debugMode) { //if debug is true
                std::cout << "pemdas started ( loop." << std::endl;
            }
            while (inputVector[i]!= ")") {
                if (inputVector[i] == "^") { //if i is a ^
                    calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                    calcVector.push_back(inputVector[i]); //add it to the back of the seat
                    i++; //advance to the next position of i
                }
                else if (inputVector[i] == "*" || inputVector[i] == "/") { //if i is a * or /
                    calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                    calcVector.push_back(inputVector[i]); //add it to the back of the ast
                    i++; //advance to the next position of i
                }
                else if (inputVector[i] == "+" || inputVector[i] == "-") { //if i is a + or -
                    calcVector.push_back(inputVector[i - 1]); //grabs the number before the operator to the back of the ast
                    calcVector.push_back(inputVector[i]); //add it to the back of the ast
                    i++; //advance to the next position of i
                }
                else;
                    calcVector.push_back(inputVector[i]); //add it to the back of the ast
                    i++; //advance to the next position of i
            }
            if (config::debugMode) { //if debug is true
                std::cout << "pemdas finished ) loop." << std::endl;
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
    }*/
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