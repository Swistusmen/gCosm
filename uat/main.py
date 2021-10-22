import os
import subprocess
from multiprocessing import Process
import time

def test_streamming_goes_on():
    if os.path.isfile("test.mp4"):
        os.remove("test.mp4")
    server= subprocess.Popen("./gCosm -lp 8554",shell=True)
    client= subprocess.Popen("./gCosm -lp 8554 -ds receive -sf test.mp4",shell=True)
    time.sleep(4)
    fileSize=os.path.getsize("test.mp4")
    assert(fileSize!=0)


