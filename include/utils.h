#ifndef UTILS_H
#define UTILS_H

//inline allows a function to be shared across multiple files and called without error
inline bool containsSubstring(const std::string& mainString, const std::vector <std::string>& subString) { //this function returns true if a main string contains within it our substring
    for (const std::string& sub : subString) {  //for every element in the substring vector
        if (mainString.find(sub) != std::string::npos) {  //try to find the substring in the mainstring
            return true;
        }
    }
    return false;
}

#endif