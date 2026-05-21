//this is the lexer, used to parse the cleaned string into a series of single token strings

#include <iostream> //required for any basic input/output operations
#include <cctype> //needed for isapha
#include <string> //imports the string library
#include <vector> //imports the vector
#include "config.h" //includes the config file containing debug variables

bool containsSubstring(const std::string& mainString, const std::vector <std::string>& subString) { //this function returns true if a main string contains within it our substring
    for (const std::string& sub : subString) {  //for every element in the substring vector
        if (mainString.find(sub) != std::string::npos) {  //try to find the substring in the mainstring
            return true;
        }
    }
    return false;
}

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

    for (int n = 0; n < inputFunction.length(); ) { //for every position in the input function
        char currentChar = inputFunction[n]; //the current character is in the n position

        if (std::isdigit(currentChar)) { //if currentChar is a digit
            currentToken.push_back(currentChar); //add it to the current token
            while (n + 1 < inputFunction.length() && std::isdigit(inputFunction[n + 1])){ //and as long as the next char is also a number
                n++; //this moves n to the next position if it exists and is a digit
                currentToken.push_back(inputFunction[n]); //add it to the end of the current token
            }
            lexedTokens.push_back(currentToken); //add the entire token we just made to the vector
            currentToken.clear(); //now clear the token so that we can collect another one
            n++;
        }

        //now find out if the next character is a character
        else if (std::isalpha(currentChar)) {
        
            std::string nextThree; //creates a string to hold the next 3 characters

            for (int i = n; i < n + 3 && i < inputFunction.length(); i++ ) { //adds the next three characters to the nextThree string
                nextThree.push_back(inputFunction[i]);
            }

            bool foundTrig = false; //because I wrapped the if statement for finding trig funtions in a for loop I need a way to tell the next else if to skip

            for (int i = 0; i < trigFunctions.size(); i++) { //creates a loop that can loop through the entire trig function vector
                if (nextThree == trigFunctions[i]) { //determines if the next three characters are a trigFunction
                    lexedTokens.push_back(nextThree); //add the entire next three string we just made to the vector
                    nextThree.clear(); //now clear the token so that we can collect another one
                    foundTrig = true; //this will make the foundtrig if statement return true and skip remaining checks for inputFunction[n] and prevent the last else from adding 1 after this adds 3
                    n += 3;
                    break; //breaks the loop the moment a match is found
                }
            }

            if (foundTrig) { } //do nothing, this just skips the following two else if and else statements if true and runs them if false
            
            else if (currentChar == 'x' || currentChar == 'e' ) { //if the next token is an x or e
                currentToken.push_back(currentChar); //add it to the currentChar string
                lexedTokens.push_back(currentToken); //add the currentChar to the 
                currentToken.clear();
                n++;
            }

            else { //if the next token us an unknown alpha print an error saying what it is and skip
                std::cout << "Lexer Error: Unhandled variable: " << currentChar <<std::endl;
                n++; //continues to the next n if the letter was unknown
            }
        }

        else if (containsSubstring(std::string(1, currentChar), operators)) { //converts the currentChar into a string so I can compare it against operators, and checks if the next token is an operator
            currentToken.push_back(currentChar); //add it to the currentChar string
                lexedTokens.push_back(currentToken); //add the currentChar to the 
                currentToken.clear();
                n++;  
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