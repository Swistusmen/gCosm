#!/bin/bash

rm uat/gCosm 
cp output/gCosm uat/gCosm

cd uat
pytest3 main.py

