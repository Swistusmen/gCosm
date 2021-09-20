#include "ProgramConfig.h"

#define DEFAULT_PORT "8554"
#define DEFALT_IP "127.0.0.1"
#define DEFAULT_URL_PATH "test"
#define DEFAULT_FILEPATH ""

class StreamingServer{
    public:
    StreamingServer(ProgramConfig driver);
    ~StreamingServer();


    protected:
    std::string ipAddress;
    std::string ipPath;
    std::string port;
    std::string filepath;
};