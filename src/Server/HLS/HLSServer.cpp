#include "HLSServer.h"

HLSServer::HLSServer(ProgramConfig config, DataChunk& dataChunk,std::shared_ptr<PipelineManager> pipManager): StreamingServer(config,dataChunk,pipManager)
{
    /*gst_init(NULL,NULL);
    loop=g_main_loop_new(NULL,FALSE);*/
}

void HLSServer::run(){

}