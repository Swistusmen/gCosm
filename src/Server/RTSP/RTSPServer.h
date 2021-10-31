#pragma once
#include <vector>

#include <gst/rtsp-server/rtsp-server.h>

#include "../StreamingServer.h"
#include "RTSPSession.h"

#include <iostream>

//TODO:- extend destructr-check how freeing port should work

class RTSPServer:public StreamingServer{
    public:
        RTSPServer(ProgramConfig driver, DataChunk& chunk,std::shared_ptr<PipelineManager>pipManager);
        ~RTSPServer();

        void run() override;

        GstRTSPMediaFactory* getFactory(){return factory;}
        void prepareMedia(GstRTSPMedia * media);
    private:
        void setupStreamsForListening();
        void setupStreamsForSending();
        
        static void mediaConfigured(GstRTSPMediaFactory * factory, RTSPServer* ptr);
        static void mediaPrepared(GstRTSPMedia * media, RTSPServer* pointer);
        static void endOfStreamSignal(GstBus* bus, GstMessage* msg);
    private:
        std::vector<RTSPSession*> streams;

        GMainLoop *loop=nullptr;
        GError* error=nullptr;
        GstElement* pipeline=nullptr;
        GstBus* bus=nullptr;
        GstRTSPServer *server=nullptr;
        GstRTSPMountPoints *mounts=nullptr;
        GstRTSPMediaFactory *factory=nullptr;
};
