#!/bin/bash

#ubuntu 20.02
#download gstreamer
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
#download gst-rtsp-server
sudo apt-get install libgstrtspserver-1.0-dev gstreamer1.0-rtsp
#download gtest
sudo apt-get install libgtest-dev
#install pytest
pip install -r uat/requeirements.txt