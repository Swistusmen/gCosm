#include "StreamingServer.h"

StreamingServer::StreamingServer(ProgramConfig driver, std::shared_ptr<DataChunk> data,std::shared_ptr<PipelineManager> pipManager):ipAddress(driver.IpAddress),ipPath(driver.AddressPath),
    port(driver.ListeningPort),bin(data){
        pipelineManager=pipManager;
        filepath=driver.DoSend?driver.LoadFile:driver.SaveFile;
        bin=data;
}

StreamingServer::~StreamingServer(){
    pipelineManager=nullptr;
}