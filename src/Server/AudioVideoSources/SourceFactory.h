#include "SavedFilm.h"
#include <memory>

class SourceFactory{
    public:
        SourceFactory(std::string name, std::string location);
        ~SourceFactory();

        std::unique_ptr<AudioVideoSource> createSource(std::string);
};