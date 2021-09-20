#pragma once
#include <memory>
#include "RTSPServer.h"
#include "../Common/DataChunk.h"

class Server{
    public:
        Server(ProgramConfig driver);
        ~Server();

        DataChunk run();

    private:
        std::unique_ptr<StreamingServer> streamingServer;
};