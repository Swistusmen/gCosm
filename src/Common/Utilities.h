#pragma once

enum class Protocol{
    None,
    RTSP,
    HLS
};

enum class TransportContainer{
    None,
    MP4,
    MKV
};

enum class VideoCodec{
    None,
    H264,
    AV1
};

//support only for AAC