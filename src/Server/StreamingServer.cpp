#include "StreamingServer.h"

StreamingServer::StreamingServer(ProgramConfig driver, DataChunk& chunk,std::shared_ptr<PipelineManager> pipManager):ipAddress(driver.IpAddress),ipPath(driver.AddressPath),
    port(driver.ListeningPort),file(chunk){
        pipelineManager=pipManager;
        filepath=driver.DoSend?driver.LoadFile:driver.SaveFile;
}
