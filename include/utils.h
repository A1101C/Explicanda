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

inline bool containsAny(const std::vector <std::string>& tokenVector, const std::vector<std::string>& inputVector) { //will check if the inputVector contains any of the tokens from the tokenVector
    for (const std::string& token : tokenVector) { //for every index in the tokenVector, token is equal to the current tokenVector index
        if (containsString(token, inputVector)) { //check if the token exists in the inputVector by using the contains string function
            return true;
        }
    }
    return false;
}

inline void replaceAll(std::string& str, const std::string& from, const std::string& to) { // called with replaceAll(inputstring, "thing to be replaced", "thing to replace with")
size_t start_pos = 0; //a special unsigned integer type is our start position variable
while((start_pos = str.find(from, start_pos)) != std::string::npos) { //search str from the start position, and continue as long as the from string is in the str string
    str.replace(start_pos, from.length(), to); //in the string, replace at the current start_pos, the from strings entire length, with the to string
    start_pos += to.length(); //increment the start position by the length of the to string
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

//takes a vector, a string to be replaced, and what to replace it with
inline std::vector<std::string> replaceStrings(const std::vector<std::string>& vectorIn, const std::string& oldStr, const std::string& newStr) { 
    std::vector<std::string> vectorOut; // Initializes the vector to hold the output
    
    //use const std::string& because vectorIn is constant
    for (const std::string& str : vectorIn) {  
        //use == for comparison, and compare str directly to oldStr
        if (str == oldStr) { 
            vectorOut.push_back(newStr); //if it matches push the new string
        } else {
            vectorOut.push_back(str);    //else keep the original string
        }
    }
    return vectorOut;
}

namespace utils {
    inline constexpr double epsilon = 1e-12; //define epsilon for double accuracy, constexpr makes it be evaluated at compile time so it is fast
}

#endif