#pragma once
#include <string>
#include <map>

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

    void mapJson(std::map<std::string,std::string> json){
        SaveFile=json["SaveFile"];
        ListeningPort=json["ListeningPort"];
        LoadFile=json["LoadFile"];
        Protocol=json["Protocol"];
        DoSend= (json["DoSend"]=="send"||json["DoSend"]=="Send")?true:false;
        AddressPath=json["AddressPath"];
        IpAddress=json["IpAddress"];
    }
};