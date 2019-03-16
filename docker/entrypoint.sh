#!/usr/bin/env bash

set -e

cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DPOSTGRES_CXX_BUILD_TESTS=ON \
    -B./build/ \
    -H.

cmake --build ./build/ -- -j2

if [[ $1 = "--run" ]]
then
    wait-for-it.sh postgres:5432

    for TEST in $(find ./build -name PostgresCxxClientTest)
    do
        ${TEST}
    done
fi
