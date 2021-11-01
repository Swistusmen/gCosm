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
def test_hls_mp4_h264_receiving_goes_on():
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

def test_hls_mp4_h264_streamming_goes_on():
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

def test_hls_mkv_av1_receiving_goes_on():
    if os.path.isdir("HLSAV1"):
        print("Test failed")
        return
    os.chdir("HLSAV1")
    server=subprocess.Popen("python3 -m http.server 8080")
    streamer=subprocess.Popen("gst-launch-1.0 -e filesrc location=rabbitAV1.mkv -v ! matroskademux name=demux ! queue ! matroskamux name=mux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=100 demux. ! queue ! aacparse ! mux.")
    receiver=subprocess.Popen(".././gCosm -ds receive -p hls -ap playlist.m3u8 -sf test.mkv -vc av1 -tc mkv")
    time.sleep(4)
    server.kill()
    streamer.kill()
    receiver.kill()
    fileSize=os.path.getsize("test.mkv")
    assert(fileSize!=0)
    os.remove("segment*")
    os.remove("playlist.m3u8")

def test_hls_mkv_av1_streamming_goes_on():
    if os.path.isdir("HLSAV1"):
        print("Test failed")
        return
    os.chdir("HLSAV1")
    server=subprocess.Popen("python3 -m http.server 8080")
    streamer=subprocess.Popen(".././gCosm -lf rabbitAV1.mkv -p hls -vc av1 -tc mkv")
    receiver=subprocess.Popen("gst-launch-1.0 -v souphttpsrc location=http://127.0.0.1:8080/playlist.m3u8 -e ! hlsdemux ! matroskademux name=demux ! queue  ! matroskamux name=mux ! filesink location=sample2.mkv demux. ! queue ! aacparse ! mux.")
    time.sleep(4)
    server.kill()
    streamer.kill()
    receiver.kill()
    fileSize=os.path.getsize("sample2.mkv")
    assert(fileSize!=0)

def test_hls_mkv_h264_receiving_goes_on():
    if os.path.isdir("HLSH264MKV"):
        print("Test failed")
        return
    os.chdir("HLSH264MKV")
    server=subprocess.Popen("python3 -m http.server 8080")
    streamer=subprocess.Popen("gst-launch-1.0 -e filesrc location=rabbitH264.mkv -v ! matroskademux name=demux ! queue ! h264parse! matroskamux name=mux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=100 demux. ! queue ! aacparse ! mux.")
    receiver=subprocess.Popen(".././gCosm -ds receive -p hls -ap playlist.m3u8 -sf test.mkv -tc mkv")
    time.sleep(4)
    server.kill()
    streamer.kill()
    receiver.kill()
    fileSize=os.path.getsize("test.mkv")
    assert(fileSize!=0)
    os.remove("segment*")
    os.remove("playlist.m3u8")

def test_hls_mkv_h264_streamming_goes_on():
    if os.path.isdir("HLSH264MKV"):
        print("Test failed")
        return
    os.chdir("HLSH264MKV")
    server=subprocess.Popen("python3 -m http.server 8080")
    streamer=subprocess.Popen(".././gCosm -lf rabbitH264.mkv -p hls -tc mkv")
    receiver=subprocess.Popen("gst-launch-1.0 -v souphttpsrc location=http://127.0.0.1:8080/playlist.m3u8 -e ! hlsdemux ! matroskademux name=demux ! queue  ! matroskamux name=mux ! filesink location=sample2.mkv demux. ! queue ! aacparse ! mux.")
    time.sleep(4)
    server.kill()
    streamer.kill()
    receiver.kill()
    fileSize=os.path.getsize("sample2.mkv")
    assert(fileSize!=0)



