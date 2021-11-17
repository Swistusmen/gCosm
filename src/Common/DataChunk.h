#pragma once
#include <string>

struct DataChunk{
    DataChunk(std::string video="", std::string coordinates=""):videoPath(video),coordinatePath(coordinates){}
    std::string videoPath;
    std::string coordinatePath;
};
