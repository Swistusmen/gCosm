#pragma once
#include <string>

#include <gst/gst.h>
#include <iostream>

#include "../../Common/ProgramConfig.h"

class AudioVideoSource{
    public:
        AudioVideoSource(ProgramConfig driver){
            doSend=driver.DoSend;
        };

        std::string getLaunchDescription(){
            if(doSend){
                return sendLaunch;
            }
            return listenLaunch;
        };
        
        bool doSourceSend(){return doSend;}
        void changeSending(){doSend=!doSend;}
    protected:
        std::string listenLaunch;
        std::string sendLaunch;

    private:
        bool doSend;
};