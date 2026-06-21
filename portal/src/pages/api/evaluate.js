// src/pages/api/evaluate.js
import { execFile } from 'child_process';
import path from 'path';
import { fileURLToPath } from 'url';

// Node.js ESM workarounds to replicate your original __dirname functionality
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

export async function POST({ request }) {
    try {
        // Read the incoming JSON body payload from the client-side fetch
        const body = await request.json();
        const { expression, xMin, xMax, xCount } = body;

        if (!expression) {
            return new Response(JSON.stringify({ error: "No expression provided" }), {
                status: 400,
                headers: { 'Content-Type': 'application/json' }
            });
        }

        // Adjust your path relative to your current file tree location inside Astro
        // Since this file lives in src/pages/api/, we step up 3 times to get to project root
        const binaryPath = path.join(__dirname, '../../../../output/engine');
        const args = [expression];

        if (expression.toLowerCase().includes('x')) {
            args.push(xMin || "0", xMax || "0", xCount || "0");
        }

        // Wrap execFile in a Promise to bridge Express style callbacks with Astro's modern async pipeline
        const result = await new Promise((resolve, reject) => {
            execFile(binaryPath, args, (error, stdout, stderr) => {
                if (error) {
                    reject({ status: 500, error: "Engine Execution Failed", details: stderr || error.message });
                    return;
                }

                const points = [];
                if (expression.toLowerCase().includes('x') && stdout) {
                    const lines = stdout.split('\n');
                    for (const line of lines) {
                        const match = line.match(/\(([^,]+),\s*([^)]+)\)/);
                        if (match) {
                            points.push({ x: match[1].trim(), y: match[2].trim() });
                        }
                    }
                }

                resolve({
                    success: true,
                    input: expression,
                    result: stdout,
                    points: points.length > 0 ? points : null
                });
            });
        });

        // Return a successful, clean web standard JSON response
        return new Response(JSON.stringify(result), {
            status: 200,
            headers: { 'Content-Type': 'application/json' }
        });

    } catch (err) {
        // Handle errors seamlessly during calculation execution
        const status = err.status || 500;
        return new Response(JSON.stringify({ error: err.error || "Internal Server Error", details: err.details || err.message }), {
            status: status,
            headers: { 'Content-Type': 'application/json' }
        });
    }
}