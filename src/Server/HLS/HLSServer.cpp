#include "HLSServer.h"

HLSServer::HLSServer(ProgramConfig config, DataChunk& dataChunk): StreamingServer(config,dataChunk)
{
    /*gst_init(NULL,NULL);
    loop=g_main_loop_new(NULL,FALSE);*/
}

void HLSServer::run(){

}