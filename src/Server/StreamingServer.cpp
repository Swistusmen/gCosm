#include "StreamingServer.h"

StreamingServer::StreamingServer(ProgramConfig driver, DataChunk& chunk):ipAddress(driver.IpAddress),ipPath(driver.AddressPath),
    port(driver.ListeningPort),file(chunk){
        filepath=driver.DoSend?driver.LoadFile:driver.SaveFile;
}
