#pragma once
#include <memory>
#include "RTSP/RTSPServer.h"
#include "HLS/HLSServer.h"
#include "../Common/Utilities.h"
#include "../Common/DataChunk.h"
#include "PipelineManager/PipelineManager.h"

class Server{
    public:
        Server(ProgramConfig driver, std::shared_ptr<PipelineManager> pipManager);
        ~Server();

        DataChunk run();

    private:
        std::unique_ptr<StreamingServer> streamingServer;
        DataChunk data;
};