#include "../Common/ProgramConfig.h"
#include <string>
#include <tuple>
#include <gst/gst.h>
#include <iostream>

static GMainLoop* tLoop;

class Transcoder{
public:
    Transcoder(ProgramConfig driver);
    bool setUpCodecsPipelines(ProgramConfig driver);

    void run();
private:
    void transcode(std::string pipelineDescription);

    static void onEOSCallback(GstBus* bus, GstElement* pip );
private:
    std::string transcodeMp4ToMKV="";
    std::string transcodeMKVToMp4="";
    std::string changeCodec="";

    std::pair<TransportContainer,VideoCodec> begin;
    std::pair<TransportContainer,VideoCodec> end;

    GError* error=nullptr;
    GstElement* pipeline=nullptr;
    GstBus* bus=nullptr;
};
