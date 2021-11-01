#!/bin/bash

rm uat/gCosm 
cp output/gCosm uat/gCosm

cd uat

mkdir HLS
cp rabbit.mp4 HLS/rabbit.mp4

pytest main.py
rm -rf HLS

