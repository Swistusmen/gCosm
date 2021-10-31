#include "PipelineManager.h"

PipelineManager::PipelineManager(ProgramConfig driver){
    rtspSendMP4H264="( filesrc location=" + driver.LoadFile+" ! qtdemux name=d d. ! queue ! rtph264pay ! pt=96 name=pay0 d. ! queue ! rtpmp4apay pt=97 name=pay1 )";
    rtspReceiveMP4H264="rtspsrc location="+driver.mapProctolToString()+"://"+driver.IpAddress+ ":"+driver.ListeningPort  +driver.AddressPath +" name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location="+driver.SaveFile+ " src. ! decodebin  ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
    hlsSendMP4H264;
    hlsReceiveeMP4H264;

    config=driver;
}

std::string PipelineManager::getPipeline(){
    if(config.SProtocol==Protocol::RTSP){
        if(config.DoSend==true){
            return rtspSendMP4H264;
        }
        return rtspReceiveMP4H264;
    }else{
        if(config.DoSend==true){
            return hlsSendMP4H264;
        }
        return hlsReceiveeMP4H264;
    }
}

bool PipelineManager::doSend(){
    return config.DoSend;
}