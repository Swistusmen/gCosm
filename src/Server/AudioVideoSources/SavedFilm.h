#include "AudioVideoSource.h"

class SavedFilm: public AudioVideoSource{
    public:
        SavedFilm(std::string filename, std::string path);
        ~SavedFilm();

        std::string getLaunchDescription() override;
    
};