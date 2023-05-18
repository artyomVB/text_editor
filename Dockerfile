FROM gcc

COPY . ./app

WORKDIR app

RUN apt update

RUN apt install -y cmake libncurses-dev

RUN mkdir build && cd build

WORKDIR build

RUN cmake .. && make

CMD /bin/bash 
