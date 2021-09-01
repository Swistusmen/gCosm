#!/bin/bash

if [[ ! -d "$output"]]
then
    mkdir output
fi

cmake -S src -B output

cd output
make
cd ..
