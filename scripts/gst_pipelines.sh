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

#transcode h.264-> av1 in mp4, aac->mp3
gst-launch-1.0 -e filesrc location=earth.mp4 ! \decodebin name=decode ! \videoscale ! 'video/x-raw,width=640,height=480' ! \av1enc ! queue ! mp4mux name=mp4mux ! filesink location=0000.mp4 \decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mp4mux.

#stream mp4 with av1 and aac


#receive mp4 and save to file (av1+aac)


#receive mp4 (h264,aac)
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test latency=0 name=src src. ! decodebin ! videoconvert ! autovideosink src. ! decodebin ! audioconvert ! autoaudiosink

#receive mp4 (h264, aac-> mpeg)
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location=test.mp4 src. ! decodebin  ! audioconvert ! lamemp3enc bitrate=128 ! queue ! mux.

#receive mp4 (h264,aac)- audio problems
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location=test.mp4 src. ! decodebin  ! audioconvert ! avenc_aac bitrate=128 ! queue ! mux.

#receive mp4 (h264,aac)
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/test name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location=test4.mp4 src. ! decodebin  ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.