#include "Transcoder.h"

/* Receive hls mp4 h264 and transcode it to mkv av1
./gCosm -p hls -gvc av1 -vc h264 -sf tego_jeszcze_nie_bylo.mp4 -tc mp4 -gtc mkv -ap playlist.m3u8 -ds receive
*/

Transcoder::Transcoder(ProgramConfig driver){
    gst_init(NULL,NULL);
    begin={driver.TContainer,driver.VCodec};
    end={driver.GTContainer,driver.GVCodec};
}

void Transcoder::run(){
    if(changeCodec!=""){
        if(begin.first!=TransportContainer::MKV)
            transcode(transcodeMp4ToMKV);
        transcode(changeCodec);
    }
    if(end.first==TransportContainer::MP4)
        transcode(transcodeMKVToMp4);
    if(end.first==TransportContainer::MKV&&changeCodec!="")
        transcode(transcodeMp4ToMKV);
}

bool Transcoder::setUpCodecsPipelines(ProgramConfig driver){
    if(driver.GVCodec==VideoCodec::None&&driver.GTContainer==TransportContainer::None){
        return false;}
    std::string filename=driver.SaveFile.substr(0,driver.SaveFile.find('.'));
    std::string newFilename="new"+driver.SaveFile.substr(0,driver.SaveFile.find('.'));
    if(begin.second!=end.second && end.second!=VideoCodec::None){
        switch(end.second){
            case VideoCodec::AV1:{
                changeCodec="filesrc location="+filename+".mkv ! decodebin name=decode ! av1enc ! queue ! matroskamux name=mux ! filesink location="+newFilename+".mkv decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
            }break;
            case VideoCodec::H264:{
                changeCodec="filesrc location="+filename+".mkv ! decodebin name=decode ! x264enc ! queue ! matroskamux name=mux ! filesink location="+newFilename+".mkv decode. ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
            }break;
    }
    }
    transcodeMp4ToMKV="filesrc location="+driver.SaveFile+" ! qtdemux name=demux ! queue ! matroskamux name=mux ! filesink location="+filename+".mkv demux. ! queue ! aacparse ! mux.";
    transcodeMKVToMp4="filesrc location="+driver.SaveFile+" ! matroskademux name=demux ! queue ! mp4mux name=mux ! filesink location="+filename+".mp4 demux. ! queue ! h264parse ! mux.";
    return true;
}

void Transcoder::transcode(std::string pipelineDescription){
    std::cout<<pipelineDescription<<std::endl;
    tLoop=g_main_loop_new(NULL,FALSE);
    pipeline=gst_parse_launch_full (pipelineDescription.c_str(), NULL, GST_PARSE_FLAG_FATAL_ERRORS, &error);
    if (!pipeline || error) {
        g_printerr ("Unable to build pipeline: %s", error->message ? error->message : "(no debug)");
    }
    bus=gst_element_get_bus(pipeline);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    gst_bus_add_signal_watch(bus);
    g_signal_connect( G_OBJECT(bus),"message::eos",(GCallback)onEOSCallback,pipeline);
    gst_object_unref(bus);
    g_main_loop_run(tLoop);
    g_main_loop_quit(tLoop);
}

void Transcoder::onEOSCallback(GstBus* bus, GstElement* pip){
    gst_element_set_state(pip,GST_STATE_NULL);
    gst_object_unref(pip);
    g_main_loop_quit(tLoop);
}




