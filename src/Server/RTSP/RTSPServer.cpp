#include "RTSPServer.h"

RTSPServer::RTSPServer(ProgramConfig driver, DataChunk& chunk):StreamingServer(driver,chunk){
    gst_init(NULL,NULL);
    loop=g_main_loop_new(NULL,FALSE);
    server=gst_rtsp_server_new();

    gst_rtsp_server_set_address(server,driver.IpAddress.c_str());
    gst_rtsp_server_set_service(server,driver.ListeningPort.c_str());
    mounts=gst_rtsp_server_get_mount_points(server);
    factory=gst_rtsp_media_factory_new();

    source=std::make_shared<SavedFilm>(driver);
}

RTSPServer::~RTSPServer(){
    if(streams.size())
        streams.clear();
    if(pipeline){
        gst_element_set_state(pipeline,GST_STATE_NULL);
        gst_object_unref(pipeline);
    }
    g_main_loop_unref(loop);
}

void RTSPServer::run(){
    if(source->doSourceSend()){
        setupStreamsForSending();
    }else{
        setupStreamsForListening();
    }
    g_main_loop_run(loop);
}

void RTSPServer::setupStreamsForSending(){
    std::string pipelineDescription=source->getLaunchDescription();
    gst_rtsp_media_factory_set_launch (factory, pipelineDescription.c_str());
    g_signal_connect(factory, "media-configure", (GCallback) mediaConfigured, this);
    gst_rtsp_mount_points_add_factory(mounts,ipPath.c_str(),factory);
    g_object_unref(mounts);
    gst_rtsp_server_attach (server, NULL);
}

void RTSPServer::setupStreamsForListening(){
    std::string pipelineDescription=source->getLaunchDescription();
    pipeline = gst_parse_launch_full (pipelineDescription.c_str(), NULL, GST_PARSE_FLAG_FATAL_ERRORS, &error);
    if (!pipeline || error) {
        g_printerr ("Unable to build pipeline: %s", error->message ? error->message : "(no debug)");
    }
    bus=gst_element_get_bus(pipeline);
    gst_bus_add_signal_watch(bus);
    g_signal_connect( G_OBJECT(bus),"message::eos",(GCallback)endOfStreamSignal,&pipeline);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

void RTSPServer::mediaPrepared(GstRTSPMedia * media,RTSPServer* pointer)
{
    auto ptr=static_cast<RTSPServer*>(pointer);
    ptr->prepareMedia(media);
}

void RTSPServer::mediaConfigured(GstRTSPMediaFactory * factory, RTSPServer* ptr){
    g_signal_connect(factory, "prepared", (GCallback) mediaPrepared, ptr);
}

void RTSPServer::endOfStreamSignal(GstBus* bus, GstMessage* msg){
    g_printerr("Message from the bus \n");
    exit (0); //temporary
}

void RTSPServer::prepareMedia(GstRTSPMedia* media){
    const guint nStreams=gst_rtsp_media_n_streams(media);
    for(int i=0;i<nStreams;i++){
        GstRTSPStream* stream;
        if(stream=gst_rtsp_media_get_stream(media,i)){
            RTSPSession* ptr=new RTSPSession();
            streams.push_back(ptr);
        }
    }
}


