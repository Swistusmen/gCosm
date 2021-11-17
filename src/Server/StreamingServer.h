#pragma once
#include "../Common/DataChunk.h"
#include "../Common/ProgramConfig.h"
#include "PipelineManager/PipelineManager.h"
#include <memory>
#include <iostream>

class StreamingServer{
    public:
    StreamingServer(ProgramConfig driver,std::shared_ptr<DataChunk> dataChunk,std::shared_ptr<PipelineManager> pipManager);
    ~StreamingServer();

    virtual void run()=0;

    protected:
        std::string ipAddress;
        std::string ipPath;
        std::string port;
        std::string filepath;
        
        std::shared_ptr<DataChunk> bin;
        std::shared_ptr<PipelineManager> pipelineManager;
};