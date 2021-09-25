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
}

void RTSPServer::run(){
    setupStreams();
    std::cout<<gst_rtsp_server_get_address(server)<<std::endl;
    std::cout<<gst_rtsp_server_get_service(server)<<std::endl;
    g_main_loop_run(loop);
}

void RTSPServer::setupStreams(){
    std::string pipelineDescription=source->getLaunchDescription();
    gst_rtsp_media_factory_set_launch (factory, pipelineDescription.c_str());
    g_signal_connect(factory, "media-configure", (GCallback) mediaConfigured, this);
    gst_rtsp_mount_points_add_factory(mounts,ipPath.c_str(),factory);
    g_object_unref(mounts);
    gst_rtsp_server_attach (server, NULL);
}


void RTSPServer::mediaPrepared(GstRTSPMedia * media,RTSPServer* pointer)
{
    auto ptr=static_cast<RTSPServer*>(pointer);
    ptr->prepareMedia(media);
}

void RTSPServer::mediaConfigured(GstRTSPMediaFactory * factory, RTSPServer* ptr){
    g_signal_connect(factory, "prepared", (GCallback) mediaPrepared, ptr);
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


