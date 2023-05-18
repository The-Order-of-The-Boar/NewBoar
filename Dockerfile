FROM ubuntu:22.04

COPY src/ ./src/
COPY build.sh .

RUN apt-get update 
RUN apt-get install -y build-essential wget libsodium23 libopus0
RUN wget -O dpp.deb https://dl.dpp.dev/ 
RUN dpkg -i dpp.deb
RUN ls

RUN ./build.sh
ENTRYPOINT [ "./NewBoar" ]
