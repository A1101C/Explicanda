
//importing dependencies
const express = require('express'); //requires the node.js express framework
const { execFile } = require('child_process'); //built in node.js tool to talk to the OS to launch and run a program
const path = require('path'); //handles universal pathing by making / and \ depending on the OS

const app = express(); //starts the node.js express framework
const port = 80; //defines the port to listen on

app.use(express.json()); //tells express to use a middleware to translate information between the backend and front end

app.use(express.static(path.join(__dirname, '../frontend'))); //tells express to look in the /frontend folder to find the webGUI

app.post('/api/evaluate', (req, res) => { //tels the server to listen for POST requests. /api/evaluate is the endpoint and throws the req into it and response back
    const { expression } = req.body; //saves the body of the request as expression

    if (!expression) { //error handling, if there is no expression then error 400
        return res.status(400).json({ error: "No expression provided" });
    }

    const binaryPath = path.join (__dirname, '../output/engine'); /*defines the binaryPath variable with path.join, which glues together the 
     __dirname which contains the location of the server.js file and uses ../ to go back one then output/engine to point at the binary */

    execFile(binaryPath, [expression], (error, stdout, stderr) => { /*this launches the engine binary and passes the expression directly to it and asynchronously waits
    for it to run and catches 3 things, any system errors, the standard output of the binary, and any standard errors with std::cerr */
        if (error) { //if the binary wasn't found or didnt launch
            return res.status(500).json({ //tells us the error code
                error: "Engine Execution Failed", //a message about what part failed
                details: stderr || error.message //gives us the details about what failed from std::cerr and the error message from here
            })
        }

        const result = stdout.trim(); //holds the answer the engine spat out
        return res.json({ //a successful json response
            success: true, //success is true
            input: expression, //contains the original math
            result: result //contains the result
        })
    })
});

app.listen(port, () => {
    console.log(`Arithmos API Server running on http://localhost:${port}`)
})

