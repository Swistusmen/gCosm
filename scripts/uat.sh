#!/bin/bash
#http server need to run in uat localization at that time
rm uat/gCosm 
cp output/gCosm uat/gCosm

cd uat
pytest main.py

rm -rf segment* playlist* test* sample*
