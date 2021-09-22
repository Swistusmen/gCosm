#include "RTSPServer.h"

RTSPServer::RTSPServer(ProgramConfig driver, DataChunk& chunk):StreamingServer(driver,chunk){
    gst_init(NULL,NULL);
    loop=g_main_loop_new(NULL,FALSE);
    server=gst_rtsp_server_new();

    driver.IpAddress="127.0.0.1";
    std::cout<<driver.ListeningPort<<std::endl;
    driver.ListeningPort="8554";
    gst_rtsp_server_set_address(server,driver.IpAddress.c_str());
    gst_rtsp_server_set_service(server,driver.ListeningPort.c_str());
    mounts=gst_rtsp_server_get_mount_points(server);
    factory=gst_rtsp_media_factory_new();

    source=std::make_shared<SavedFilm>(driver);
}

RTSPServer::~RTSPServer(){
    if(streams.size())
        streams.clear();
}

void RTSPServer::run(){
    std::cout<<"run\n";
    setupStreams();
    std::cout<<gst_rtsp_server_get_address(server)<<std::endl;
    std::cout<<gst_rtsp_server_get_service(server)<<std::endl;
    g_main_loop_run(loop);
}

void RTSPServer::setupStreams(){
    //in the future it should be  deleted
    auto c=std::string("rabbit.mp4").c_str();
    gchar* pipelineDescription= g_strdup_printf ("( "
      "filesrc location=\"%s\" ! qtdemux name=d "
      "d. ! queue ! rtph264pay pt=96 name=pay0 "
      "d. ! queue ! rtpmp4apay pt=97 name=pay1 " ")", c);

    //source->getLaunchDescription();
    gst_rtsp_media_factory_set_launch (factory, pipelineDescription);
    std::cout<<"RTSP Server\n";
    //g_signal_connect(factory, "media-configure", (GCallback) mediaConfigured, this);
    g_signal_connect(factory, "media-configure", (GCallback) media_configure_cb, factory);
    g_free(pipelineDescription);
    
    std::cout<<ipPath<<std::endl;
    gst_rtsp_mount_points_add_factory(mounts,"/test",factory);
    g_object_unref(mounts);
    gst_rtsp_server_attach (server, NULL);
}

/*
void RTSPServer::mediaPrepared(GstRTSPMedia * media,RTSPServer* pointer)
{
    std::cout<<"Media prepared\n";
    auto ptr=static_cast<RTSPServer*>(pointer);
    ptr->prepareMedia(media);
}

void RTSPServer::mediaConfigured(GstRTSPMediaFactory * factory, RTSPServer* ptr){
    std::cout<<"Media configured\n";
    g_signal_connect(factory, "prepared", (GCallback) mediaPrepared, ptr);
}
*/

void RTSPServer::prepareMedia(GstRTSPMedia* media){
    std::cout<<"My fun\n";
    const guint nStreams=gst_rtsp_media_n_streams(media);
    for(int i=0;i<nStreams;i++){
        GstRTSPStream* stream;
        if(stream=gst_rtsp_media_get_stream(media,i)){
            RTSPSession* ptr=new RTSPSession();
            streams.push_back(ptr);
        }
    }
}

void RTSPServer::media_configure_cb (GstRTSPMediaFactory * factory, GstRTSPMedia * media)
{
  g_signal_connect (media, "prepared", (GCallback) media_prepared_cb, factory);
}

void
RTSPServer::media_prepared_cb (GstRTSPMedia * media)
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
  }}


