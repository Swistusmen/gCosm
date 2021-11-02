#include "../Common/ProgramConfig.h"
#include <string>
#include <tuple>
#include <gst/gst.h>

class Transcoder{
public:
    Transcoder(ProgramConfig driver);
    void setUpCodecsPipelines(ProgramConfig driver);

    void run();
private:

    void transcodeContainer(TransportContainer begin,TransportContainer end);
    void transcode(std::string pipelineDescription);
private:
    std::string transcodeMp4ToMKV="";
    std::string transcodeMKVToMp4="";
    std::string changeCodec="";

    std::pair<TransportContainer,VideoCodec> begin;
    std::pair<TransportContainer,VideoCodec> end;

    GMainLoop *loop=nullptr;
    GError* error=nullptr;
    GstElement* pipeline=nullptr;
    GstBus* bus=nullptr;
};
