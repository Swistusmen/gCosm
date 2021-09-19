#include "test.h"


TestRunner::TestRunner(std::string filename){
  loop = g_main_loop_new (NULL, FALSE);
  server = gst_rtsp_server_new ();
  
  g_object_set (server, "service", port, NULL);
 
  str = g_strdup_printf ("( "
      "filesrc location=\"%s\" ! qtdemux name=d "
      "d. ! queue ! rtph264pay pt=96 name=pay0 "
      "d. ! queue ! rtpmp4apay pt=97 name=pay1 " ")", filename.c_str());
}

void TestRunner::run(){
     mounts = gst_rtsp_server_get_mount_points (server);
    factory = gst_rtsp_media_factory_new ();
  gst_rtsp_media_factory_set_launch (factory, str);
  g_signal_connect (factory, "media-configure", (GCallback) media_configure_cb,
      factory); //sygnal emitowany gdy media sa juz skonfigurowane*/
  g_free (str);

  /* attach the test factory to the /test url */
  gst_rtsp_mount_points_add_factory (mounts, "/test", factory);

  /* don't need the ref to the mapper anymore */
  g_object_unref (mounts);

  /* attach the server to the default maincontext */
  gst_rtsp_server_attach (server, NULL);
    g_main_loop_run (loop);
}

void
TestRunner::media_configure_cb (GstRTSPMediaFactory * factory, GstRTSPMedia * media)
{
  g_signal_connect (media, "prepared", (GCallback) media_prepared_cb, factory);
}

void
TestRunner::media_prepared_cb (GstRTSPMedia * media)
{
  guint i, n_streams;

  n_streams = gst_rtsp_media_n_streams (media);

  GST_INFO ("media %p is prepared and has %u streams", media, n_streams);

  for (i = 0; i < n_streams; i++) {
    GstRTSPStream *stream;
    GObject *session;

    stream = gst_rtsp_media_get_stream (media, i);
    if (stream == NULL)
      continue;

    session = gst_rtsp_stream_get_rtpsession (stream);
    GST_INFO ("watching session %p on stream %u", session, i);
  }
}