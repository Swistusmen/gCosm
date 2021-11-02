#pragma once

#include "../../Common/ProgramConfig.h"
#include <string>
#include <iostream>

class PipelineManager{
    public:
    PipelineManager(ProgramConfig config);

    std::string getPipeline();
    bool doSend();

    void buildPipeline(ProgramConfig dirver);

    private:
        std::string rtspSendMP4H264;
        std::string rtspReceiveMP4H264;
        std::string hlsSendMP4H264;
        std::string hlsReceiveMP4H264;
        std::string hlsSendMKVAV1;
        std::string hlsReceiveMKVAV1;
        std::string hlsSendMKVH264;
        std::string hlsReceiveMKVH264;

        std::string currentHLSPipeline;

        ProgramConfig config;
};