FROM ubuntu:20.04

RUN apt-get update
RUN apt-get install -y software-properties-common
EXPOSE 40000
RUN mkdir -p /multmatrix
COPY mainServer /multmatrix
#CMD sleep 1000
WORKDIR /multmatrix
RUN chmod 777 mainServer
CMD ./mainServer
