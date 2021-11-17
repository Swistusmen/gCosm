#pragma once
#include <memory>
#include "RTSP/RTSPServer.h"
#include "HLS/HLSServer.h"
#include "../Common/Utilities.h"
#include "../Common/DataChunk.h"
#include "PipelineManager/PipelineManager.h"
#include <iostream>

class Server{
    public:
        Server(ProgramConfig driver, std::shared_ptr<PipelineManager> pipManager, std::shared_ptr<DataChunk> dataChunk=nullptr);

        ~Server();

        DataChunk run();
    private:
        std::unique_ptr<StreamingServer> streamingServer;
        std::shared_ptr<DataChunk>  bin;
};