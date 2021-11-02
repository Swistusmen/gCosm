#include "Transcoder.h"

Transcoder::Transcoder(ProgramConfig driver){
    begin={driver.TContainer,driver.VCodec};
    end={driver.GTContainer,driver.GVCodec};
}

void Transcoder::run(){
    gst_init(NULL,NULL);
    if(changeCodec!=""&&begin.first!=TransportContainer::MKV)
        transcode(transcodeMp4ToMKV);
    if(changeCodec!="")
        transcode(changeCodec);
    if(end.first==TransportContainer::MP4)
        transcode(transcodeMKVToMp4);
}

void Transcoder::setUpCodecsPipelines(ProgramConfig driver){
    if(driver.GVCodec==VideoCodec::None||driver.GTContainer==TransportContainer::None){
        return;}
    std::string filename=driver.SaveFile.substr(0,'.')+".mkv";
    std::string newFilename="new"+driver.SaveFile.substr(0,'.')+".mkv";
    if(begin.second!=end.second){
        switch(end.second){
            case VideoCodec::AV1:{
                changeCodec="filesrc location="+filename+" ! decodebin name=decode ! av1enc ! queue ! matroskamux name=mux ! filesink location="+newFilename+" decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
            }break;
            case VideoCodec::H264:{
                changeCodec="filesrc location="+filename+" ! decodebin name=decode ! x264enc ! queue ! matroskamux name=mux ! filesink location="+newFilename+" decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
            }break;
    }
    std::string transcodeMp4ToMKV="filesrc location="+driver.SaveFile+" ! decodebin name=decode ! queue ! matroskamux name=mux ! filesink location="+filename+" decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
    std::string transcodeMKVToMp4="filesrc location="+driver.SaveFile+" ! decodebin name=decode ! queue ! qtmux name=mux ! filesink location="+filename+" decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
    }
}

void Transcoder::transcode(std::string pipelineDescription){
    pipeline=gst_parse_launch_full (pipelineDescription.c_str(), NULL, GST_PARSE_FLAG_FATAL_ERRORS, &error);
    if (!pipeline || error) {
        g_printerr ("Unable to build pipeline: %s", error->message ? error->message : "(no debug)");
    }
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}



