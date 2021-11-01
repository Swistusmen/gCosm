import os
import subprocess
from multiprocessing import Process
import time

def test_rtsp_streamming_goes_on():
    if os.path.isfile("test.mp4"):
        os.remove("test.mp4")
    server= subprocess.Popen("./gCosm -lp 8554",shell=True)
    client= subprocess.Popen("./gCosm -lp 8554 -ds receive -sf test.mp4",shell=True)
    time.sleep(4)
    server.kill()
    client.kill()
    fileSize=os.path.getsize("test.mp4")
    assert(fileSize!=0)

#HLS
#add codecs tests- thanks to the gst-discoverer-1.0 and grep
def test_hls_receiving_goes_on():
    if os.path.isdir("HLS"):
        print("Test failed")
        return
    os.chdir("HLS")
    server=subprocess.Popen("python3 -m http.server 8080")
    streamer=subprocess.Popen("gst-launch-1.0 filesrc location=rabbit.mp4 ! qtdemux name=demux ! queue ! h264parse disable-passthrough=true ! mpegtsmux name=mux ! hlssink playlist-root=http://127.0.0.1:8080 max-files=100 playlist-length=0 demux. ! queue ! aacparse ! mux.")
    receiver=subprocess.Popen(".././gCosm -ds receive -p hls -ap playlist.m3u8 -sf test.mp4")
    time.sleep(4)
    server.kill()
    streamer.kill()
    receiver.kill()
    fileSize=os.path.getsize("test.mp4")
    assert(fileSize!=0)
    os.remove("segment*")
    os.remove("playlist.m3u8")

def test_hls_streamming_goes_on():
    if os.path.isdir("HLS"):
        print("Test failed")
        return
    os.chdir("HLS")
    server=subprocess.Popen("python3 -m http.server 8080")
    streamer=subprocess.Popen(".././gCosm -lf rabbit.mp4 -p hls ")
    receiver=subprocess.Popen("gst-launch-1.0 -v souphttpsrc location=http://127.0.0.1:8080/playlist.m3u8 -e ! hlsdemux ! tsdemux name=demux ! queue ! h264parse ! mp4mux name=mux ! filesink location=sample2.mp4 demux. ! queue ! aacparse ! mux.")
    time.sleep(4)
    server.kill()
    streamer.kill()
    receiver.kill()
    fileSize=os.path.getsize("sample2.mp4")
    assert(fileSize!=0)
    




