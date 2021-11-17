#include "Server.h"

Server::Server(ProgramConfig driver, std::shared_ptr<PipelineManager> pipManager){
    //TODO: -change when next servers will be added
    if(driver.SProtocol==Protocol::RTSP)
        streamingServer= std::make_unique<RTSPServer>(driver,data,pipManager);
    else if(driver.SProtocol==Protocol::HLS){
        streamingServer=std::make_unique<HLSServer>(driver,data,pipManager);
    }
}

Server::~Server(){
    streamingServer.reset();
}

DataChunk Server::run(){
    DataChunk dataChunk;
    if(streamingServer)
        streamingServer->run();
    return dataChunk;
}