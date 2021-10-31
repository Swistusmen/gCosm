#Handy pipelines

#receive stream and save to file (mp4):
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test ! rtph264depay ! h264parse ! mp4mux ! filesink location=file.mp4

#receive and play stream:
 gst-launch-1.0 playbin uri=rtsp://127.0.0.1:8554/test

 gst-launch-1.0 rtspsrc location=rtsp://localhost:8554/test latency=100 ! queue ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! videoscale ! video/x-raw,width=640,height=480 ! autovideosink

 #play stream from file:
gst-launch-1.0 playbin uri=file:///${path_to_file}

#stream
gst-launch-1.0 -v filesrc location=rabbit.mp4 ! qtdemux name=demux demux. ! h264parse ! queue ! mpegtsmux ! rtpmp2tpay ! udpsink host=127.0.0.1 port=8554

gst-launch-1.0 filesrc location= rabbit.mp4 ! qtdemux ! queue ! h264parse ! rtph264pay ! udpsink rtsp://127.0.0.1:8554/test

gst-launch-1.0 -v filesrc location=rabbit.mp4 ! x264enc ! rtph264pay name=pay0 pt=96 ! udpsink rtsp://127.0.0.1:8554/test

#transcode h.264-> av1 in mp4, aac->aac
gst-launch-1.0 -e filesrc location=earth.mp4 ! \decodebin name=decode ! \videoscale ! 'video/x-raw,width=640,height=480' ! \av1enc ! queue ! mp4mux name=mp4mux ! filesink location=0000.mp4 \decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mp4mux.

#stream mp4 with av1 and aac! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=5


#receive mp4 and save to file (av1+aac)


#receive mp4 (h264,aac)
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test latency=0 name=src src. ! decodebin ! videoconvert ! autovideosink src. ! decodebin ! audioconvert ! autoaudiosink

#receive mp4 (h264, aac-> mpeg)
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location=test.mp4 src. ! decodebin  ! audioconvert ! lamemp3enc bitrate=128 ! queue ! mux.

#receive mp4 (h264,aac)- audio problems
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location=test.mp4 src. ! decodebin  ! audioconvert ! avenc_aac bitrate=128 ! queue ! mux.

#receive mp4 (h264,aac)
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location=test4.mp4 src. ! decodebin  ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.

#stream h264 hls from file
gst-launch-1.0 filesrc location=rabbit.mp4 ! decodebin ! mpegtsmux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=5
python3 -m http.server 8080 #in the location where there is a server
#accessible on http//:127.0.0.1:8080/playlist.m3u8

#another one:
gst-launch-1.0 filesrc location=rabbit.mp4 ! qtdemux ! queue ! decodebin ! x264enc ! mpegtsmux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=5

#streamming av1 on ubuntu 21.1.0 (formating to av1)
gst-launch-1.0 filesrc location=rabbit.mp4 ! qtdemux ! queue ! decodebin ! av1enc ! matroskamux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=5

#receiving av1 on ubuntu 21.1.0
gst-launch-1.0 -v souphttpsrc location=http://127.0.0.1:8080/playlist.m3u8 ! filesink location=sample.mkv

#stream from file
gst-launch-1.0 filesrc location=rabbit.mp4 ! qtdemux ! queue ! decodebin ! x264enc ! mpegtsmux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=100

#stream matroska file http- no transcoding:
gst-launch-1.0 filesrc location=fat_bunny.mkv -v ! matroskademux ! h264parse ! matroskamux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=5

#transcode from mp4 to mkv (h264->av1) #TODO: 
gst-launch-1.0 -e filesrc location=rabbit.mp4 ! \decodebin name=decode ! av1enc ! queue ! matroskamux name=mux ! filesink location=rabbitAV1.mkv \decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.

#stream AV1 mkv-> mkv (no transcoding)- only video: FIXME: TODO:
gst-launch-1.0 -e filesrc location=rabbitAV1.mkv -v ! matroskademux ! matroskamux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=100

#save hls stream to file (mkv-> mkv) (av1->av1), only video: FIXME: TODO: 
gst-launch-1.0 -v souphttpsrc location=http://127.0.0.1:8080/playlist.m3u8 -e ! hlsdemux ! matroskademux ! matroskamux ! filesink location=sample2.mkv

#hls stream mp4 h264, aac TODO:
gst-launch-1.0 filesrc location=rabbit.mp4 ! qtdemux name=demux ! queue ! h264parse disable-passthrough=true ! mpegtsmux name=mux ! hlssink playlist-root=http://127.0.0.1:8080 max-files=100 playlist-length=0 demux. ! queue ! aacparse ! mux.

#hls receiver mp4 h264 aac TODO:
gst-launch-1.0 -v souphttpsrc location=http://127.0.0.1:8080/playlist.m3u8 -e ! hlsdemux ! tsdemux name=demux ! queue ! h264parse ! mp4mux name=mux ! filesink location=sample2.mp4 demux. ! queue ! aacparse ! mux.

#hls stream mkv av1, aac TODO:
gst-launch-1.0 -e filesrc location=rabbitAV1.mkv -v ! matroskademux name=demux ! queue ! matroskamux name=mux ! \hlssink playlist-root=http://127.0.0.1:8080 target-duration=5 max-files=100 demux. ! queue ! aacparse ! mux.

#hls receive mkv av1, aac TODO:
gst-launch-1.0 -v souphttpsrc location=http://127.0.0.1:8080/playlist.m3u8 -e ! hlsdemux ! matroskademux name=demux ! queue  ! matroskamux name=mux ! filesink location=sample3.mkv demux. ! queue ! aacparse ! mux.

#hls stream mp4 (h26, aac)->mkv (av1,aac) TODO: -but in the future
gst-launch-1.0 filesrc location=rabbit.mp4 ! qtdemux name=demux ! queue ! h264parse ! avdec_h264 ! av1enc ! matroskamux name=mux ! hlssink playlist-root=http://127.0.0.1:8080 max-files=100 playlist-length=0 demux. ! queue ! aacparse ! mux.

