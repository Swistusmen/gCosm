#include "../StreamingServer.h"
#include "../AudioVideoSources/SourceFactory.h"
#include "RTSPStream.h"
#include <map>

class RTSPServer:public StreamingServer{
    public:
        RTSPServer(ProgramConfig driver);
        ~RTSPServer();

    private:
        void setup_streams();
        
    private:
        SourceFactory sourceFactory;
        RTSPStream stream;
};
