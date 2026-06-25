
#compile the cpp binary

FROM gcc:12.2 AS cpp-builder

WORKDIR /explicanda/src/

#copy cpp source files
COPY main.cpp /explicanda/src/
COPY ./src/* /explicanda/src/
COPY ./include/* /explicanda/src/

#create output folder and compile binary
RUN mkdir -p output && \
    g++ -std=c++17 -O3 *.cpp -I . -o output/engine



#build the astro ssr server

FROM node:22-slim

WORKDIR /explicanda/portal/

#copy package properties to install Node modules
COPY portal/package*.json ./
RUN npm install

#copy all Astro project source files into the container
COPY portal/ ./

#copy the compiled cpp binary into the parent directory where evaluate.js expects it
COPY --from=cpp-builder /explicanda/src/output/engine /explicanda/output/engine

#ensure the process has permission to run the compiled cpp binary
RUN chmod +x /explicanda/output/engine

#run the astro build command
RUN npm run build

#astro's node server defaults to port 4321
EXPOSE 4321

#set environment variables so astro listens on all network interfaces inside Docker
ENV HOST=0.0.0.0
ENV PORT=4321

#command to launch the compiled astro server
CMD ["node", "./dist/server/entry.mjs"]