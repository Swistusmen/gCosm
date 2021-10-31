#pragma once
#include "../StreamingServer.h"



class HLSServer: public StreamingServer{
    public:
    HLSServer(ProgramConfig config, DataChunk& dataChunk);

    void run() override;

    private:
    void SetupForListening();
    void SetupForStreamming();
    
};
