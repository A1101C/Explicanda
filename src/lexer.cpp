//this is the lexer, used to parse the cleaned string into a series of single token strings

#include <iostream> //required for any basic input/output operations
#include <cctype> //needed for isalpha
#include <string> //imports the string library
#include <vector> //imports the vector
#include "config.h" //includes the config file containing debug variables
#include "utils.h" //this has the containsString function


//Begining of the lexer function
std::vector < std::string > lexer(std::string inputFunction) {

    if (config::debugMode) { //prints the inputFunction for the lexer to the console if debug is true
        std::cout << "Lexer started with string inputFunction:   " << inputFunction << std::endl;
    }

    std::vector < std::string > lexedTokens; //initializes the vector to hold the tokens

    std::string currentToken; //creates a string to hold the token currently being assembled

    std::vector < std::string > operators = {"(", ")", "^", "*", "/", "+", "-", "="}; //makes a vector to hold operators
    std::vector < std::string > trigFunctions = {"sin", "cos", "tan", "sec", "csc", "cot"}; //a vector holding trig functions
    std::vector < std::string > logFunctions = {"log", "ln"}; //a vector to hold log, ln, and e. 

    for (int n = 0; n < inputFunction.length(); ) { //for every position in the input function
        char currentChar = inputFunction[n]; //the current character is in the n position

        if (std::isdigit(currentChar)) { //if currentChar is a digit
            currentToken.push_back(currentChar); //add it to the current token
            while (n + 1 < inputFunction.length() && std::isdigit(inputFunction[n + 1])){ //and as long as the next char exists and is also a number
                n++; //this moves n to the next position if it exists and is a digit
                currentToken.push_back(inputFunction[n]); //add it to the end of the current token
            }
            lexedTokens.push_back(currentToken); //add the entire token we just made to the vector
            currentToken.clear(); //now clear the token so that we can collect another one
            n++; //advance to the next position in the inputFunction
        }

        //now find out if the next character is a character
        else if (std::isalpha(currentChar)) {
        
            std::string nextThree; //creates a string to hold the next 3 characters

            for (int i = n; i < n + 3 && i < inputFunction.length(); i++ ) { /*for i equal to n while i is less than n+3 and i is less than the input length
                the reason for that is because we want the next 3 parts of the string including our current n and the next two but not the third, hence the less than
                rather than a less than or equal to. we also want to make sure we are not trying to read a position that does not exist, like n when n is the last
                part of the string and i+1 would be a non existant space*/
                nextThree.push_back(inputFunction[i]); //adds the next three characters to the nextThree string
            }

            bool foundTrig = false; //because I wrapped the if statement for finding trig functions in a for loop I need a way to tell the next else if to skip
            bool foundLog = false; //because I wrapped the if statement for finding log functions in a for loop I need a way to tell the next else if to skip

            for (const std::string& trig : trigFunctions) {   //check if the length of the string is long enough to be a trig function
                if (n + trig.length() <= inputFunction.length() && inputFunction.substr(n, trig.length()) == trig) { //makes sure input Function is long enough to have a trig function, and loops through the trig function vector to determine if one exists in the inputFunction and assigns it to trig
                    lexedTokens.push_back(trig); //put the trig substring in the lexedTokens vector
                    
                    n += trig.length(); //skips n to go past the length of the trig function
                    foundTrig = true; //found trig is true
                    break; //immediately leave the if and for loops
                }
            }

            if (foundTrig) { 
                continue; //skip back to the top
            } 

            for (int i = 0; i < logFunctions.size(); i++) { //creates a loop to look through the log function vector
                if (nextThree == logFunctions[i]) { //determines if the next 3 characters contain a log function
                    if (nextThree == std::string("log")){ //determines if the next three characters are exactly log
                        lexedTokens.push_back(nextThree); //add the entire next three string we just made to the vector
                        nextThree.clear(); //now clear the token so that we can collect another one
                        foundLog = true; //this will make the foundLog if statement return true and skip remaining checks for inputFunction[n] and prevent the last else from adding 1 after this adds 3
                        n += 3; //advance to the next position in the inputFunction after the found log function
                        /*if (inputFunction[n] == 'x') { //if the next char is x
                            lexedTokens.push_back("("); //add ( to the token vector before the x
                            lexedTokens.push_back("x"); //add x to the token vector
                            lexedTokens.push_back(")"); //add ) to the token vector after the x
                            n += 1; //advance to the next position
                        }*/ // commented out due to and issue with logx in the parser
                    }
                }

                else if (nextThree.substr(0, 2) == "ln") {// if its not exactly log it must be ln
                    nextThree.clear(); //clear the next three
                    lexedTokens.push_back("ln"); //add ln to the token vector
                    foundLog = true; //found log is true
                    n += 2; //advance two positions to get past the ln
                    /*if (inputFunction[n] == 'x') { //if the next char is x
                        lexedTokens.push_back("("); //add ( to the token vector before the x
                        lexedTokens.push_back("x"); //add x to the token vector
                        lexedTokens.push_back(")"); //add ) to the token vector after the x
                        n += 1; //advance to the next position
                    }*/ //commented out due to an issue with the parser and (x)  
                }
            }  
            
            if (foundLog) { } //do nothing, this just skips the following else if and else statements if true and runs them if false

            else if (currentChar == 'x' || currentChar == 'e' ) { //if the next token is an x or e
                lexedTokens.push_back("*"); //add * to the token vector before the x or e
                //lexedTokens.push_back("("); //add ( to the token vector before the x or e
                currentToken.push_back(currentChar); //add it to the currentChar string
                lexedTokens.push_back(currentToken); //add the currentToken to the token vectors
                //lexedTokens.push_back(")"); //add ) to the token vector after the x or e

                if (n + 1 < inputFunction.length()) { //if the next position exists
                    std::string nextChar(1, inputFunction[n + 1]); //make it equal to the string nextChar, the (1,inputFunction) is to say that the char we are pulling from input function is the 1st character in the string nextChar
                    if (!containsString(nextChar, operators)) { //if the next character is not an operator
                        lexedTokens.push_back("*"); //put * between x and it.
                    }
                }
                currentToken.clear(); //clear the current token
                n++; //advance to the next position in the inputFunction
            }

            else { //if the next token us an unknown alpha print an error saying what it is and skip
                std::cout << "Lexer Error: Unhandled variable: " << currentChar <<std::endl;
                n++; //continues to the next n if the letter was unknown
            }
        }

        else if (containsString(std::string(1, currentChar), operators)) { //converts the currentChar into a string so I can compare it against operators, and checks if the next token is an operator
            currentToken.push_back(currentChar); //add it to the currentChar string
                lexedTokens.push_back(currentToken); //add the currentToken to the token vector
                currentToken.clear(); //clears the currentToken
                n++; //advance to the next position in the inputFunction
        }
    
        else {
            std::cout << "Lexer Error: Unknown String in n = " << n << " position." << std::endl; //if we run into an unknown string print its position
            n++; //advance by one so we can continue evaluating the function
        }
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