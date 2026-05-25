#ifndef UTILS_H
#define UTILS_H

#include <string> //because lexer will work with std::string
#include <vector> //imports the vector

//inline allows a function to be shared across multiple files and called without error

inline bool containsString(const std::string& mainString, const std::vector <std::string>& subString) { //this function returns true if a main string contains within it our substring
    for (const std::string& sub : subString) {  //for every element in the substring vector
        if (mainString == sub) {  //if the main string is exactly the substring
            return true;
        }
    }
    return false;
}

inline void replaceAll(std::string& str, const std::string& from, const std::string& to) { // called with replaceAll(inputstring, "thing to be replaced", "thing to replace with")
size_t start_pos = 0;
while((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); 
    }
}

inline int operatorCounter(const std::vector<std::string>& inputVector) {   
    std::vector < std::string > operators = {"(", ")", "^", "*", "/", "+", "-", "="}; //makes a vector to hold operators
    int operatorCounter = 0; //initializes a variable to keep track of the count of operators

    for (int n = 0; n < inputVector.size(); ++n) { //this loop will check every position in the inputVector
         std::string currentToken(inputVector[n]); //make it equal to the first character of the next string in vector position n
            if (containsString(currentToken, operators)) { //check if the current token is an operator
                operatorCounter += 1; //increase the operator count by 1
        }
    }
    return operatorCounter; //pass the operator count back out of the function
}

#endif