#!/bin/bash

rm uat/gCosm 
cp output/gCosm uat/gCosm

cd uat

mkdir HLS
mkdir HLSAV1
mkdir HLSH264MKV
cp rabbit.mp4 HLS/rabbit.mp4
cp rabbitAV1.mkv HLSAV1/rabbitAV1.mkv
cp rabbitH264.mkv HLSH264MKV/rabbitH264

pytest main.py
rm -rf HLS
rm -rf HLSAV1
rm -rf HLSH264MKV

