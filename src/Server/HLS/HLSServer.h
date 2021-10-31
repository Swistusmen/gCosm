#pragma once
#include "../StreamingServer.h"

class HLSServer: public StreamingServer{
    public:
    HLSServer(ProgramConfig config, DataChunk& dataChunk,std::shared_ptr<PipelineManager> pipManager);

    void run() override;

    private:
    void SetupForListening();
    void SetupForStreamming();
    
};
