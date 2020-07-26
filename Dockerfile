#getting base image
FROM ubuntu:20.04

LABEL maintainer="serdar@karaman.dev"

ARG TZ=Europe/Istanbul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get -y install devscripts build-essential lintian dh-make
RUN apt-get -y install qtdeclarative5-dev qt5-default libjack-jackd2-dev
RUN apt-get -y install lcov gcovr

WORKDIR /root
ADD . / TicTacToe/
