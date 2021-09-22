#pragma once
#include "../Common/DataChunk.h"
#include "../Common/ProgramConfig.h"

class StreamingServer{
    public:
    StreamingServer(ProgramConfig driver,DataChunk& chunk);

    virtual void run()=0;

    protected:
        std::string ipAddress;
        std::string ipPath;
        std::string port;
        std::string filepath;

        DataChunk& file;
};