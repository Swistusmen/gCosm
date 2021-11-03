#include "Parser/parser.h"
#include "Server/Server.h"
#include "Transcoder/Transcoder.h"
#include "PipelineManager/PipelineManager.h"
#include <iostream>

int main(int argc,char* argv[])
{
    Parser parser;
    auto driver=parser.createProgramDriver(argc,argv);
    std::cout<<driver.message;
    auto pipelineManager=std::make_shared<PipelineManager>(driver);
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
