#compile the C++ Engine

#downloads the GNU compiler collection to use the g++ compiler
FROM gcc:12.2 AS cpp-builder

#set up a workspace folder for building
WORKDIR /arithmos-machine

#copy the source files to the current directory
COPY main.cpp /arithmos-machine/
COPY ./src/*.cpp /arithmos-machine/src/
COPY ./include/*.h /arithmos-machine/include

#creates the output folder and compiles the binary to it
RUN mkdir -p output && \
    g++ -std=c++17 -O3 main.cpp src/*.cpp -I ./include -o output/engine

#build the node.js API web hub with a tiny linux layer with nodejs 18 pre installed
FROM node:18-slim

#set working directory for our Node application
WORKDIR /arithmos-machine/portal/

#copy package properties to install Node modules
COPY portal/package*.json /arithmos-machine/portal
RUN cd /arithmos-machine/portal && npm install

#copy the express portal backend files and frontend interface
COPY portal/ /arithmos-machine/portal/
COPY frontend/ /arithmos-machine/frontend/

#ensure the node process has permission to run the compiled C++ binary
RUN chmod +x /arithmos-machine/output/engine

#expose the port the express app listens on
EXPOSE 80

#set the execution directory to the portal folder where server.js resides
WORKDIR /arithmos-machine/portal

#command to launch your web engine application
CMD ["node", "server.js"]