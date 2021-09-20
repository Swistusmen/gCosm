#include <string>

class AudioVideoSource{
    public:
        AudioVideoSource();
        ~AudioVideoSource();

        virtual std::string getLaunchDescription();

    protected:
        std::string launch;
};