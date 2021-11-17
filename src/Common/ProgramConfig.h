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
    bool SensorData=false;
    std::string message="";
    bool doStream=false;
    TransportContainer TContainer=TransportContainer::MP4;
    VideoCodec VCodec= VideoCodec::H264;
    TransportContainer GTContainer=TransportContainer::None;
    VideoCodec GVCodec=VideoCodec::None;


    Protocol mapStringToProctol(std::string protocol){
        if(protocol=="rtsp")
            return Protocol::RTSP;
        else if(protocol=="hls")
            return Protocol::HLS;
        else
            return Protocol::None;
    }

    std::string mapProctolToString(Protocol sprot){
        if(sprot==Protocol::RTSP)
            return "rtsp";
        else if(sprot==Protocol::HLS)
            return "hls";
        else
            return "none";
    }

    std::string mapTContainerToString(TransportContainer tcon){
        if(tcon==TransportContainer::MP4)
            return "mp4";
        else if(tcon==TransportContainer::MKV)
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

    std::string mapVCodecToString(VideoCodec v){
        if(VideoCodec::H264==v)
            return "h264";
        else if(VideoCodec::AV1==v)
            return "av1";
        else
            return "none";
    }

    std::string print(){
        std::string result="ListeningPort: "+ListeningPort+"\n"
            +"SaveFile: "+ SaveFile+"\n"
            +"LoadFile: "+LoadFile+"\n"
            +"Protocol: "+mapProctolToString(SProtocol)+"\n"
            +"DoSend: "+(DoSend?"yes":"no")+"\n"
            +"AddressPath: "+ AddressPath+"\n"
            +"SensorData:"+(SensorData?"True":"False")+"\n"
            +"IpAddress: "+IpAddress+"\n"
            +"TransportContainer:"+mapTContainerToString(TContainer)+"\n"
            +"VideoCodec:"+mapVCodecToString(VCodec)+"\n"
            +"GoalTransportContainer:"+mapTContainerToString(GTContainer)+"\n"
            +"GoalVideoCodec:"+mapVCodecToString(GVCodec)+"\n";
            return result;
    }

    void mapJson(std::map<std::string,std::string> json){
        SaveFile=json["SaveFile"];
        ListeningPort=json["ListeningPort"];
        LoadFile=json["LoadFile"];
        SProtocol=mapStringToProctol(json["Protocol"]);
        DoSend= (json["DoSend"]=="send"||json["DoSend"]=="Send")?true:false;
        AddressPath=json["AddressPath"];
        SensorData=((json["SensorData"]=="0"||json["SensorData"]=="false")?false:true);
        IpAddress=json["IpAddress"];
        TContainer=mapStringToTContainer(json["TransportContainer"]);
        VCodec=mapStringToVCodec(json["VideoCodec"]);
        GTContainer=mapStringToTContainer(json["GoalTransportContainer"]);
        GVCodec=mapStringToVCodec(json["GoalVideoCodec"]);
    }
};