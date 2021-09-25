#pragma once
#include <vector>

#include <gst/rtsp-server/rtsp-server.h>

#include "../StreamingServer.h"
#include "../AudioVideoSources/SourceFactory.h"
#include "RTSPSession.h"

#include <iostream>

//TODO- extend destructr-check how freeing port should work

class RTSPServer:public StreamingServer{
    public:
        RTSPServer(ProgramConfig driver, DataChunk& chunk);
        ~RTSPServer();

        void run() override;

        GstRTSPMediaFactory* getFactory(){return factory;}
        void prepareMedia(GstRTSPMedia * media);
    private:
        //for listening to a stream
        void setupStreamsForListening();
        //for sending streaming
        void setupStreamsForSending();
        
        static void mediaConfigured(GstRTSPMediaFactory * factory, RTSPServer* ptr);
        static void mediaPrepared(GstRTSPMedia * media, RTSPServer* pointer);
    private:
        //std::shared_ptr<SourceFactory> sourceFactory;
        std::shared_ptr<AudioVideoSource> source;
        std::vector<RTSPSession*> streams;

        GMainLoop *loop;
        GstRTSPServer *server;
        GstRTSPMountPoints *mounts;
        GstRTSPMediaFactory *factory;
};
