#pragma once

#include "../../Common/ProgramConfig.h"
#include <string>
#include <iostream>

class PipelineManager{
    public:
    PipelineManager(ProgramConfig config);

    std::string getPipeline();
    bool doSend();

    private:
        std::string rtspSendMP4H264;
        std::string rtspReceiveMP4H264;
        std::string hlsSendMP4H264;
        std::string hlsReceiveeMP4H264;
        std::string hlsSendMKVAV1;
        std::string hlsReceiveMKVAV1;
        std::string hlsSendMKVH264;
        std::string hlsReceiveeMKV264;

        ProgramConfig config;
};