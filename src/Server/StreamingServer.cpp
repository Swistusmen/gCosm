#include "StreamingServer.h"

StreamingServer::StreamingServer(ProgramConfig driver, DataChunk& chunk,std::shared_ptr<PipelineManager> pipManager):ipAddress(driver.IpAddress),ipPath(driver.AddressPath),
    port(driver.ListeningPort),file(chunk){
        std::cout<<"Wejscie Streamming Server constructor\n";
        pipelineManager=pipManager;
        filepath=driver.DoSend?driver.LoadFile:driver.SaveFile;
        std::cout<<"Wyjscie Streamming Server constructor\n";
}

StreamingServer::~StreamingServer(){
    pipelineManager=nullptr;
}