# `graphpoints.cpp`

## Coordinate Generation and Value Mapping

`graphpoints.cpp` handles the systematic evaluation of a parsed mathematical function across a defined geometric domain. By sampling values at equal spaces from a minimum bound to a maximum bound, it yields an array of coordinate pairs suitable for discrete continuous plotting or graphing utility modules.

---

## The Graphing Logic

When an evaluation requests coordinate generation, the system instantiates structural variables, calculates bounds configurations, and computes individual steps within a linear progression loop:

### 1. Structural Components & Floating Point Snapping
* **`roundToEpsilon()`**: A functional floating-point snapping routine that uses an input epsilon constraint to filter out machine division background noise from double values.
* **`doubletoString()`**: Flushes an isolated `std::ostringstream` memory buffer to convert a raw numeric `double` directly into a clean alphanumeric string token without trailing garbage characters.

### 2. Domain Sampling Configuration
The code uses three parameter constraints passed to the main generation algorithm (`xMin`, `xMax`, `xCount`) to determine space tracking attributes:

* **Total Tracking Domain Space (`xRange`)**: Formulated as:
  $$xRange = xMax - xMin$$
* **Resolution Segment Offset (`xStep`)**: Determined by dividing the total space configuration slice by the total target coordinates sample resolution:
  $$xStep = \frac{xRange}{xCount}$$

### 3. Main Step Resolution Loop
The function initiates a standard incremental `for` loop that covers indices from `0` through `xCount` inclusive (`n <= xCount`), executing the following operations on each pass:

* **Coordinate Target Translation**: The current step index `n` determines the physical translation distance from the base parameter:
  $$xOffset = xStep \times n$$
  $$currentX = xMin + xOffset$$
* **Literal Token Injection**: Converts `currentX` into a string using `doubletoString()`. It then invokes `replaceStrings()` to swap out every single instance of the symbolic variable token `"x"` inside the parsed sequence with the literal numeric string.
* **Interpreter Execution Routing**: The temporary array payload (`xFunction`) is routed directly to the system execution module via `interpreter(xFunction)`. This evaluates the mathematical instructions down to raw machine-level statements and outputs a final precision `double` scalar returned as `currentY`.
* **Tuple Record Storing**: The resolved numeric pairs are bound inside a `std::pair<double, double>` container structure and appended to the tracking collection vector (`xyPairs`).

### 4. Diagnostics Mode Tracking
If `config::debugMode` evaluates to true, the utility prints standard contextual streams tracking `xRange`, `xStep`, every current `xFunction` array state, numerical configurations of `currentX` and `currentY`, and tracking loop iteration offsets to the standard system console output stream.

---

## Visual Control Flow

```mermaid
graph TD
    Start([graphpoints Called]) --> Setup[Fetch epsilon from utils namespace]
    Setup --> RangeCalc[xRange = xMax - xMin<br>xStep = xRange / xCount]
    
    %% Loop Initialization
    RangeCalc --> LoopStart{n = 0; n <= xCount ?}
    
    %% Loop Steps
    LoopStart -- Yes --> CalcX[xOffset = xStep * n<br>currentX = xMin + xOffset]
    CalcX --> SerializeX[Convert currentX to String via doubletoString]
    
    SerializeX --> InjectVariable[xFunction = replaceStrings parsedFunction, 'x', currentXstring]
    InjectVariable --> RunInterpreter[currentY = interpreter xFunction]
    
    RunInterpreter --> DebugCheck{config::debugMode true?}
    DebugCheck -- Yes --> PrintDiagnostics[Print current xFunction tokens, currentX, currentY, and xOffset] --> RecordPair
    DebugCheck -- No --> RecordPair[Push structure pair currentX, currentY into xyPairs]
    
    RecordPair --> IncrementLoop[n++] --> LoopStart
    
    %% Exit Paths
    LoopStart -- No --> Return[Return complete xyPairs Vector Tuple]
    Return --> End([End Evaluation Function])