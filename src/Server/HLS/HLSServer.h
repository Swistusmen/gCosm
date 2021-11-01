#pragma once
#include "../StreamingServer.h"
#include <gst/gst.h>
#include <iostream>

class HLSServer: public StreamingServer{
    public:
    HLSServer(ProgramConfig config, DataChunk& dataChunk,std::shared_ptr<PipelineManager> pipManager);
    ~HLSServer();

    void run() override;

    private:
    void setupForListening(std::string pipelineDescription);
    void setupForStreamming(std::string pipelineDescription);

    private:
    GMainLoop *loop=nullptr;
    GError* error=nullptr;
    GstElement* pipeline=nullptr;
    GstBus* bus=nullptr;
};
