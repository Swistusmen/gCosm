#pragma once
#include <string>

struct ProgramConfig{
    std::string ListeningPort="";
    std::string SaveFile="";
    std::string LoadFile="";
    std::string Protocol="rtsp";
    bool DoSend=false;
    std::string AddressPath="";
    std::string IpAddress="";
    //SensorData
    std::string message="";
    bool doStream=false;

    std::string print(){
        std::string result="ListeningPort: "+ListeningPort+"\n"
            +"SaveFile: "+ SaveFile+"\n"
            +"LoadFile: "+LoadFile+"\n"
            +"Protocol: "+Protocol+"\n"
            +"DoSend: "+(DoSend?"yes":"no")+"\n"
            +"AddressPath: "+ AddressPath+"\n"
            +"IpAddress: "+IpAddress+"\n";
            return result;
    }
};