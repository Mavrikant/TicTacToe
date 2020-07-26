#!/bin/bash

docker build -t tttbuild_env:1.0 .
docker run -it  --name tttbuild_result --workdir /root/TicTacToe tttbuild_env:1.0 bash -c "./build.sh"
docker cp tttbuild_result:/root/TicTacToe/ ./docker_build/
docker rm tttbuild_result