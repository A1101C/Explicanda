# `lexer.cpp`

## Tokenization

`lexer.cpp` handles the tokenization of the cleaned mathematical expression string passed to it. It breaks the continuous string down into a vector of distinct, manageable token strings (e.g., numbers, operators, variables, and functions) so that the parser can later process them into a syntax tree.

---

## The Lexer Logic

When a string is passed to the lexer, it processes it character by character and returns a `std::vector<std::string>` based on the following logic:

### 1. Initialization
* Several variables and vectors are initialized to hold temporary values as the string is lexed.
* **`lexedTokens`**: The final vector of strings that will be returned containing the tokenized function.
* **`currentToken`**: A temporary string buffer used to assemble multi-character tokens.
* **Lookup Vectors**: Pre-defined lists for `operators` (`(`, `)`, `^`, `*`, `/`, `+`, `-`, `=`), `trigFunctions` (`sin`, `cos`, `tan`, etc.), and `logFunctions` (`log`, `ln`).

### 2. Main Character Loop
The lexer sets up a `for` loop that iterates through the `inputFunction` using index `n`. At the start of each iteration, it extracts `currentChar` at the `n`-th position. The code then runs through a series of conditional checks:

* **Digits (Numbers):** It checks if `currentChar` is a digit. If it is, the character is appended to `currentToken`. A `while` loop then looks ahead: as long as the next index (`n + 1`) is within bounds and is also a digit, `n` is incremented and the digit is appended. This ensures multi-digit numbers are kept together. Once a non-digit is encountered, `currentToken` is pushed to `lexedTokens`, cleared, and `n` advances.

* **Alphabetical Characters (Functions & Variables):**
  If `currentChar` is alphabetical (`isalpha`), the lexer checks for multi-character functions or variables:
  * **Trigonometric Functions**: It loops through the `trigFunctions` vector. If the substring starting at `n` matches a trig function, the full function name is pushed to `lexedTokens`, `n` is advanced past the length of that function, and the loop restarts.
  * **Logarithmic Functions**: If no trig function matches, it performs the same substring match against the `logFunctions` vector (handling `log` and `ln` dynamically).
  * **Variables & Implicit Multiplication (`x`, `X`, `e`)**: If the character is an explicit variable or constant (`x`, `X`, or `e`), it normalizes `X` to `x`. 
    * **Left-Side Implicit Multiplication**: It checks the *previous* character (`n - 1`). If it was a digit, it automatically inserts a multiplication token (`*`) into `lexedTokens` before the variable.
    * **Right-Side Implicit Multiplication**: It checks the *next* character (`n + 1`). If it exists and is *not* an operator, it automatically inserts a multiplication token (`*`) after the variable.
  * **Unhandled Variables**: If an alphabetical character doesn't match any of the above, a `Lexer Error` is printed to the console, and it skips to the next character.

* **Operators:**
  If `currentChar` matches any string inside the `operators` vector, it is treated as a single token. It is pushed into `lexedTokens`, and `n` is incremented.

* **Unknown Characters:**
  If a character fails all conditions, a `Lexer Error` is printed displaying the invalid position, and `n` increments to skip it.

### 3. Debug and Output
If `config::debugMode` is enabled, the lexer prints the initial input string at the start and prints the final array of wrapped tokens (e.g., `[sin], [(], [2], [*], [x], [)]`) to the console before returning `lexedTokens`.

---

## Visual Control Flow


```mermaid
graph TD
    Start([Lexer Started]) --> Init[Initialize vectors: operators, trigFunctions, logFunctions]
    Init --> LoopStart{n < inputFunction.length?}
    
    %% Loop Evaluation
    LoopStart -- Yes --> GetChar[currentChar = inputFunction n]
    LoopStart -- No --> DebugCheck{config::debugMode true?}

    %% Digits Branch
    GetChar --> IsDigit{std::isdigit?}
    IsDigit -- Yes --> ConsumeDigits[Accumulate consecutive digits into currentToken]
    ConsumeDigits --> PushDigit[Push currentToken to lexedTokens & Clear]
    PushDigit --> AdvanceDigit[n++] --> LoopStart

    %% Alpha Branch
    IsDigit -- No --> IsAlpha{std::isalpha?}
    
    %% Trig Sub-branch
    IsAlpha -- Yes --> CheckTrig{Matches Trig Function?}
    CheckTrig -- Yes --> PushTrig[Push trig string to lexedTokens]
    PushTrig --> AdvanceTrig[n += trig.length] --> LoopStart
    
    %% Log Sub-branch
    CheckTrig -- No --> CheckLog{Matches Log Function?}
    CheckLog -- Yes --> PushLog[Push log string to lexedTokens]
    PushLog --> AdvanceLog[n += log.length] --> LoopStart
    
    %% Variable Sub-branch
    CheckLog -- No --> CheckVar{Is x, X, or e?}
    CheckVar -- Yes --> ImplicitLeft{Previous char a digit?}
    ImplicitLeft -- Yes --> InsertMultLeft[Push '*' to lexedTokens] --> ImplicitRight
    ImplicitLeft -- No --> ImplicitRight{Next char NOT an operator?}
    ImplicitRight -- Yes --> PushVar[Push variable to lexedTokens] --> InsertMultRight[Push '*' to lexedTokens] --> AdvanceVar[n++] --> LoopStart
    ImplicitRight -- No --> PushVar2[Push variable to lexedTokens] --> AdvanceVar
    
    %% Unhandled Alpha
    CheckVar -- No --> UnhandledAlpha[Print Unhandled Variable Error]
    UnhandledAlpha --> AdvanceErrorAlpha[n++] --> LoopStart

    %% Operator Branch
    IsAlpha -- No --> IsOperator{Is character an operator?}
    IsOperator -- Yes --> PushOp[Push operator to lexedTokens]
    PushOp --> AdvanceOp[n++] --> LoopStart
    
    %% Unknown Character Branch
    IsOperator -- No --> UnknownChar[Print Unknown String Error]
    UnknownChar --> AdvanceUnknown[n++] --> LoopStart

    %% Exit Paths
    DebugCheck -- Yes --> PrintTokens[Print token list to console] --> Return
    DebugCheck -- No --> Return([Return lexedTokens])