#include "Parser/parser.h"
#include "Server/Server.h"
#include "Transcoder/Transcoder.h"
#include "PipelineManager/PipelineManager.h"
#include "Server/HTTP/HTTPServer.h"
#include <iostream>

/*
1. napisanie konstruktora serwera DONE: 
2. Napisanie funkcji zmieniajace path DONE:
3. Testy DONE: 
4. Testy calej apki (czy dziala po wylaczeniu flag) DONE:
5. Commit DONE:
6. Napisanie obsługi http zaleznie od inputu
7. Zmiana dataChunk:
    -jest przyjmowany przez aplikacje
    -ma strukture
*/

int main(int argc,char* argv[])
{
    Parser parser;
    auto driver=parser.createProgramDriver(argc,argv);
    std::cout<<driver.message;
    auto pipelineManager=std::make_shared<PipelineManager>(driver);
    /*HTTPServer http;
    http.getCoordinates("http://192.168.0.185:8080", "/TODO.txt");*/
    
    if(driver.doStream){
        std::cout<<driver.print()<<std::endl;
        Server server(driver,pipelineManager);
        server.run();
        Transcoder transcoder(driver);
        if(transcoder.setUpCodecsPipelines(driver))
            transcoder.run();
    }
    return 0;
}
