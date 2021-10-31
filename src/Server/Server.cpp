#include "Server.h"

Server::Server(ProgramConfig driver, std::shared_ptr<PipelineManager> pipManager){
    //#TODO -change when next servers will be added
    if(driver.SProtocol==Protocol::RTSP)
        streamingServer= std::make_unique<RTSPServer>(driver,data,pipManager);
    
}

Server::~Server(){

}

DataChunk Server::run(){
    DataChunk dataChunk;
    streamingServer->run();
     //tutaj musi byc  odpalenie watku z serverer i jego funkcja run

    return dataChunk;
}