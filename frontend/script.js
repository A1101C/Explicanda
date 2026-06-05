document.getElementById('evaluateBtn').addEventListener('click', sendExpression); //searches the html file for the evaluate button and waist for it to be clicked to run sendExpression
document.getElementById('expressionInput').addEventListener('keypress', function(e) { //when the user types a button in the expressionInput grab it (e) means event
    if (e.key === 'Enter') { //if the user presses the enter key
        sendExpression(); //activate sendExpression
    }
});

async function sendExpression() { //defines sendExpression and lets it run asynchronously
    const inputElement = document.getElementById('expressionInput'); //this and the following lines create references so that the HTML elements can be quickly read or manipulated
    const xMinElement = document.getElementById('xMinInput'); //creates a local interface bridge to the graphing minimum boundary field block
    const xMaxElement = document.getElementById('xMaxInput'); //creates a local interface bridge to the graphing maximum boundary field block
    const xCountElement = document.getElementById('xCountInput'); //creates a local interface bridge to the point generation count field block
    const resultContainer = document.getElementById('resultContainer'); //creates connection to the hidden result box segment
    const resultText = document.getElementById('resultText'); //creates connection to the direct text placeholder area
    const tableContainer = document.getElementById('tableContainer'); //creates an interface anchor for injection of the structural data grid table
    const expressionValue = inputElement.value.trim(); //grab the text string from the inputElement and trims it
    const xMinValue = xMinElement ? xMinElement.value.trim() : "0"; //reads the custom graphing start bounds or falls back to standard zero string
    const xMaxValue = xMaxElement ? xMaxElement.value.trim() : "0"; //reads the custom graphing termination bounds or falls back to standard zero string
    const xCountValue = xCountElement ? xCountElement.value.trim() : "0"; //reads the total point generation density steps or falls back to standard zero string

    if (!expressionValue) { //if there is no expression
        alert("Please enter a valid expression."); //tells the user to enter a valid expression
        return;
    }

    try { //now try and catch makes it so if it fails to calculate the program doesn't crash
        resultText.innerText = "Evaluating..."; //while it is calculating say evaluating
        if (tableContainer) { //checks if the visual table storage div element is available in document tree
            tableContainer.innerHTML = ""; //clears away any previous data grids from past calculations to make space
        }
        
    const response = await fetch('/api/evaluate', { //references the evaluation response to be fetched as response and awaits for it
                method: 'POST', //uses post to talk to the api
                headers: { //opens the transaction request headers configuration mapping block
                    'Content-Type': 'application/json' //tells the middleware that this data is being sent as json
                },

                body: JSON.stringify({ expression: expressionValue, xMin: xMinValue, xMax: xMaxValue, xCount: xCountValue }) //converts the expression and graphing bounds parameters to json
            
            });

     const data = await response.json(); //turns the response it awaited for from express back into json

        if (response.ok && data.success) { //checks that the response was okay and it received data
            resultContainer.classList.remove('hidden'); //unhide the results box so we can put data into it
            resultText.innerHTML = `<strong>Input:</strong> ${data.input}<br><strong>Output:</strong> ${data.result}`; //displays the data if everything is good
            if (data.points && tableContainer) { //evaluates if coordinate tracking rows exist and destination container elements are present
                let tableHtml = "<table class='points-table'><thead><tr><th>X Value</th><th>Y Value</th></tr></thead><tbody>"; //begins assembly string for data grid structure with table headers
                
                for (const pt of data.points) { //loops over every single object entry inside the coordinate results matrix
                    tableHtml += `<tr><td>${pt.x}</td><td>${pt.y}</td></tr>`; //appends formatted row blocks housing distinct coordinate metrics into the grid string
                }
                
                tableHtml += "</tbody></table>"; //appends closing element markers for data grid array sections
                tableContainer.innerHTML = tableHtml; //injects raw structural text layout elements directly into the active viewport layout frame

            }
        } 
        else { //else for handling conditions where failed or returned error
            resultText.innerText = `Error: ${data.error || "Something went wrong"}`; //says something went wrong if there was a problem
        }
    } 
    catch (error) { //this is the other part of a try catch,if for some reason it fails to try then it gives this error
        console.error("Fetch operation failed:", error); //this will be hidden in the browsers developer tab saying there was a fetch error
        resultText.innerText = "Error connecting to the math server backend."; //this says there was an error on the results box for the user
    }
}