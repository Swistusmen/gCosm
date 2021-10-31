#pragma once
#include <string>
#include <map>
#include "Utilities.h"

struct ProgramConfig{
    std::string ListeningPort="";
    std::string SaveFile="";
    std::string LoadFile="";
    Protocol SProtocol=Protocol::None;
    bool DoSend=false;
    std::string AddressPath="";
    std::string IpAddress="";
    //SensorData
    std::string message="";
    bool doStream=false;
    TransportContainer TContainer=TransportContainer::MP4;
    VideoCodec VCodec= VideoCodec::H264;


    Protocol mapStringToProctol(std::string protocol){
        if(protocol=="rtsp")
            return Protocol::RTSP;
        else if(protocol=="hls")
            return Protocol::HLS;
        else
            return Protocol::None;
    }

    std::string mapProctolToString(){
        if(SProtocol==Protocol::RTSP)
            return "rtsp";
        else if(SProtocol==Protocol::HLS)
            return "hls";
        else
            return "none";
    }

    std::string mapTContainerToString(){
        if(TContainer==TransportContainer::MP4)
            return "mp4";
        else if(TContainer==TransportContainer::MKV)
            return "mkv";
        else
            return "none";
    }

    TransportContainer mapStringToTContainer(std::string container){
        if(container=="mp4")
            return TransportContainer::MP4;
        else if(container=="mkv")
            return TransportContainer::MKV;
        else
            return TransportContainer::None;
    }

    VideoCodec mapStringToVCodec(std::string codec){
        if(codec=="h264")
            return VideoCodec::H264;
        else if(codec=="av1")
            return VideoCodec::AV1;
        else
            return VideoCodec::None;
    }

    std::string mapVCodecToString(){
        if(VideoCodec::H264==VCodec)
            return "h264";
        else if(VideoCodec::AV1==VCodec)
            return "av1";
        else
            return "none";
    }

    std::string print(){
        std::string result="ListeningPort: "+ListeningPort+"\n"
            +"SaveFile: "+ SaveFile+"\n"
            +"LoadFile: "+LoadFile+"\n"
            +"Protocol: "+mapProctolToString()+"\n"
            +"DoSend: "+(DoSend?"yes":"no")+"\n"
            +"AddressPath: "+ AddressPath+"\n"
            +"IpAddress: "+IpAddress+"\n"
            +"TransportContainer:"+mapTContainerToString()+"\n"
            +"VideoCodec:"+mapVCodecToString()+"\n";
            return result;
    }

    void mapJson(std::map<std::string,std::string> json){
        SaveFile=json["SaveFile"];
        ListeningPort=json["ListeningPort"];
        LoadFile=json["LoadFile"];
        SProtocol=mapStringToProctol(json["Protocol"]);
        DoSend= (json["DoSend"]=="send"||json["DoSend"]=="Send")?true:false;
        AddressPath=json["AddressPath"];
        IpAddress=json["IpAddress"];
        TContainer=mapStringToTContainer(json["TransportContainer"]);
        VCodec=mapStringToVCodec(json["VideoCodec"]);
    }
};