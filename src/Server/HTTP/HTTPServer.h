#include <iostream>

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

#include "../../Common/DataChunk.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams; 

class HTTPServer{
    public:
        HTTPServer()=default;
        HTTPServer(std::string p, std::string q);

    public: //rest methods
        void getCoordinates(std::string ip="", std::string path="");

        void changePath(std::string p){path=p;}
        void setBin(std::shared_ptr<DataChunk> chunk){bin=chunk;}

    private:
    std::string path="";
    std::string query="";
    std::shared_ptr<DataChunk> bin;
};

