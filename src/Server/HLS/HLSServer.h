#pragma once
#include "../StreamingServer.h"
#include <gst/gst.h>
#include <iostream>

static GMainLoop *loop=nullptr;

class HLSServer: public StreamingServer{
    public:
    HLSServer(ProgramConfig config, std::shared_ptr<DataChunk> dataChunk,std::shared_ptr<PipelineManager> pipManager);
    ~HLSServer();

    void run() override;

    private:
    void setupPipeline(std::string pipelineDescription);

    static void onEOSCallback(GstBus* bus, GstElement* pipeline);

    private:
    GError* error=nullptr;
    GstElement* pipeline=nullptr;
    GstBus* bus=nullptr;
};
