#!/bin/bash

rm uat/gCosm 
cp output/gCosm uat/gCosm

cd uat
pytest main.py

