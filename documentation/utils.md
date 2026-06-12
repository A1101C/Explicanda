# `utils.h`

## Overview

`utils.h` contains inline utility functions and constant definitions that support the parsing, tokenization, and string manipulation operations throughout the math engine. These functions provide robust mechanisms for vector searching, string replacement, operator counting, and mathematical precision management.

---

## Utility Functions

The file provides five primary helper functions designed to be shared across multiple compilation units without linker conflicts using the `inline` keyword.

### 1. `containsString`
Checks if a given string matches exactly with any string element within a provided lookup vector.

* **Signature:** `inline bool containsString(const std::string& mainString, const std::vector<std::string>& subString)`
* **Logic:** Iterates through every element in the `subString` vector. If an exact match with `mainString` is found, it returns `true`. If the loop finishes without a match, it returns `false`.

### 2. `containsAny`
Determines if an input vector contains *any* of the tokens specified in a reference token vector.

* **Signature:** `inline bool containsAny(const std::vector<std::string>& tokenVector, const std::vector<std::string>& inputVector)`
* **Logic:** Iterates through each token in `tokenVector` and leverages `containsString` to check if that token exists inside `inputVector`. Returns `true` on the first match, and `false` otherwise.

### 3. `replaceAll`
Performs in-place global substring replacement on a standard string, modifying the source string directly.

* **Signature:** `inline void replaceAll(std::string& str, const std::string& from, const std::string& to)`
* **Logic:** Uses `std::string::find` starting at index `0`. While the `from` substring is located (i.e., not equal to `std::string::npos`), it executes `str.replace` at that position for the length of `from`, substitutes it with `to`, and advances the search pointer past the newly inserted string to avoid infinite loops.

### 4. `operatorCounter`
Counts the total number of mathematical operator tokens present within a tokenized vector.

* **Signature:** `inline int operatorCounter(const std::vector<std::string>& inputVector)`
* **Logic:** Initializes a local lookup vector containing supported operators (`(`, `)`, `^`, `*`, `/`, `+`, `-`, `=`) and a counter set to `0`. It loops through each string element of `inputVector` and increments the counter by `1` every time `containsString` identifies the element as an operator.

### 5. `replaceStrings`
Creates a copy of a string vector where all instances of a specific string token are substituted with a replacement token.

* **Signature:** `inline std::vector<std::string> replaceStrings(const std::vector<std::string>& vectorIn, const std::string& oldStr, const std::string& newStr)`
* **Logic:** Allocates a new output vector `vectorOut`. It iterates through each string in `vectorIn` using a constant reference. If an element exactly matches `oldStr`, `newStr` is pushed into the output vector; otherwise, the original string is retained. Returns the populated `vectorOut`.

---

## Constants & Namespaces

### Namespace `utils`
Provides encapsulated mathematical utilities to prevent global namespace pollution.

* **`utils::epsilon`**: An `inline constexpr double` set to `1e-12` ($10^{-12}$). This constant is evaluated at compile time for maximum performance and is utilized to handle floating-point precision tolerances and safe equality comparisons.

---

## Visual Control Flow

```mermaid
graph TD
    Start([Utility Call]) --> Choice{Which Function?}

    %% containsString
    Choice --> |containsString| CS_Loop{For each sub in subString}
    CS_Loop --> |Match Found| CS_True[Return true]
    CS_Loop --> |Next / End| CS_Check{More elements?}
    CS_Check -- No --> CS_False[Return false]

    %% containsAny
    Choice --> |containsAny| CA_Loop{For each token in tokenVector}
    CA_Loop --> |In inputVector?| CA_Match{containsString?}
    CA_Match -- Yes --> CA_True[Return true]
    CA_Match -- No --> CA_Loop
    CA_Loop --> |Finished| CA_False[Return false]

    %% replaceAll
    Choice --> |replaceAll| RA_Find{str.find from found?}
    RA_Find -- Yes --> RA_Replace[Replace from with to]
    RA_Replace --> RA_Advance[Advance start_pos] --> RA_Find
    RA_Find -- No --> RA_End([Exit Function])

    %% operatorCounter
    Choice --> |operatorCounter| OP_Loop{For each token in inputVector}
    OP_Loop --> |Is Operator?| OP_Check{containsString?}
    OP_Check -- Yes --> OP_Inc[operatorCounter++] --> OP_Loop
    OP_Check -- No --> OP_Loop
    OP_Loop --> |Finished| OP_Return([Return operatorCounter])

    %% replaceStrings
    Choice --> |replaceStrings| RS_Loop{For each str in vectorIn}
    RS_Loop --> |str == oldStr?| RS_Check{Match?}
    RS_Check -- Yes --> RS_PushNew[Push newStr to vectorOut] --> RS_Loop
    RS_Check -- No --> RS_PushOld[Push original str to vectorOut] --> RS_Loop
    RS_Loop --> |Finished| RS_Return([Return vectorOut])