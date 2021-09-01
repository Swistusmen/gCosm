#!/bin/bash

if [[ ! -d "$output_test"]]
then
    mkdir output_test
fi

cmake -S tst -B output_test

cd output_test
make
./gCosmTest
cd ..