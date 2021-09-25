#pragma once
#include <string>

#include <gst/gst.h>

#include "../../Common/ProgramConfig.h"

class AudioVideoSource{
    public:
        AudioVideoSource(ProgramConfig driver){};

        std::string getLaunchDescription(){return launch;};

    protected:
        std::string launch;
};