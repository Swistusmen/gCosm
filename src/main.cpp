#include "Parser/parser.h"
#include "Server/Server.h"
#include <iostream>

int main(int argc,char* argv[])
{
    Parser parser;
    auto driver=parser.createProgramDriver(argc,argv);
    std::cout<<driver.message;
    if(driver.doStream){
        Server server(driver);
        server.run();
    }
    return 0;
}
