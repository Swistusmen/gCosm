#pragma once
#include <string>

#include <gst/gst.h>

#include "../../Common/ProgramConfig.h"

class AudioVideoSource{
    public:
        AudioVideoSource(ProgramConfig driver){};

        gchar* getLaunchDescription(){return launch;};

    protected:
        gchar* launch;
};