#include <string>

struct ProgramConfig{
    int ListeningPort=-1;
    std::string SaveFile="";
    std::string LoadFile="";
    std::string Protocol="rtsp";
    bool DoSend=false;
    std::string AddressPath="";
    std::string IpAddress="";
    //SensorData
    std::string message="";
    bool doStream=false;
};