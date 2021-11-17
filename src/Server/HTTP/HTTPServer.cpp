#include "HTTPServer.h"

HTTPServer::HTTPServer(std::string ip, std::string q):query(q),path(ip){}

void HTTPServer::getCoordinates(std::string pat, std::string q){
    q=(q==""?query:q);
    pat=(pat==""?path:pat);

    if(pat=="")
        throw std::logic_error("Path is not initialized");
    if(bin==nullptr)
        throw  std::logic_error("HTTP need to have a data bin");

    auto fileStream=std::make_shared<ostream>();

    pplx::task<void> requestTask=fstream::open_ostream(U(bin->coordinatePath)).then([=](ostream outFile)
    {
        *fileStream=outFile;

        //http client to make requests
        http_client client(U(pat));

        uri_builder builder(U(q));
        return client.request(methods::GET, builder.to_string());        

    })
    .then([=](http_response response){
        printf("Received response status code:%u\n", response.status_code());

        return response.body().read_to_end(fileStream->streambuf());
    })
    .then([=](size_t){
        return fileStream->close();
    });

    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }
}
