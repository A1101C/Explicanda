document.getElementById('evaluateBtn').addEventListener('click', sendExpression); //searches the html file for the evaluate button and waist for it to be clicked to run sendExpression
document.getElementById('expressionInput').addEventListener('keypress', function(e) { //when the user types a button in the expressionInput grab it (e) means event
    if (e.key === 'Enter') { //if the user presses the enter key
        sendExpression(); //activate sendExpression
    }
});

async function sendExpression() { //defines sendExpression and lets it run asynchronously
    const inputElement = document.getElementById('expressionInput'); //this and the following two lines create references so that the HTML elements can be quickly read or manipulated
    const resultContainer = document.getElementById('resultContainer');
    const resultText = document.getElementById('resultText');
    
    const expressionValue = inputElement.value.trim(); //grab the text string from the inputElement and trims it

    if (!expressionValue) { //if there is no expression
        alert("Please enter a valid expression."); //tells the user to enter a valid expression
        return;
    }

    try { //now try and catch makes it so if it fails to calculate the program doesn't crash
        resultText.innerText = "Evaluating..."; //while it is calculating say evaluating
        resultContainer.classList.remove('hidden'); //accesses the css classes to grab the class hidden

        
        const response = await fetch('http://localhost:8080/api/evaluate', { //references the evaluation response to be fetched as response and awaits for it
            method: 'POST', //uses post to talk to the api
            headers: {
                'Content-Type': 'application/json' //tells the middleware that this data is being sent as json
            },
            body: JSON.stringify({ expression: expressionValue }) //converts the expression and stuff to json
        });

        const data = await response.json(); //turns the response it awaited for from express back into json

        if (response.ok && data.success) { //checks that the response was okay and it received data
            resultText.innerHTML = `<strong>Input:</strong> ${data.input}<br><strong>Output:</strong> ${data.result}`; //displays the data if everything is good
        } else {
            resultText.innerText = `Error: ${data.error || "Something went wrong"}`; //says something went wrong if there was a problem
        }
    } catch (error) { //this is the other part of a try catch,if for some reason it fails to try then it gives this error
        console.error("Fetch operation failed:", error); //this will be hidden in the browsers developer tab saying there was a fetch error
        resultText.innerText = "Error connecting to the math server backend."; //this says there was an error on the results box for the user
    }
}