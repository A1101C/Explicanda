#compile the C++ Engine

#downloads the GNU compiler collection to use the g++ compiler
FROM gcc:12.2 AS cpp-builder

#set up a workspace folder for building
WORKDIR /usr/src/arithmos-core

#copy the source files to the current directory
COPY main.cpp ./
COPY ./src/*.cpp ./
COPY ./include/*.h ./

#creates the output folder and compiles the binary to it
RUN mkdir -p ../output && \
    g++ -std=c++17 -O3 main.cpp cleaner.cpp lexer.cpp parserast.cpp interpreter.cpp -o ../output/engine

#build the node.js API web hub with a tiny linux layer with nodejs 18 pre installed
FROM node:18-slim

#set working directory for our Node application
WORKDIR /usr/src/app

#copy package properties to install Node modules
COPY portal/package*.json ./portal/
RUN cd portal && npm install

#copy the express portal backend files and frontend interface
COPY portal/ ./portal/
COPY frontend/ ./frontend/

#pull the compiled C++ binary from Stage 1 into the exact relative folder expected by server.js
COPY --from=cpp-builder /usr/src/output/engine ./output/engine

#ensure the node process has permission to run the compiled C++ binary
RUN chmod +x ./output/engine

#expose the port your Express app listens on
EXPOSE 8080

#set the execution directory to the portal folder where server.js resides
WORKDIR /usr/src/app/portal

#command to launch your web engine application
CMD ["node", "server.js"]