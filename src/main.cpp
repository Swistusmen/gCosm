#include "parser.h"
#include "test.h"
#include "Server/Server.h"
#include <iostream>

int main(int argc,char* argv[])
{
    Parser parser;
    auto driver=parser.createProgramDriver(argc,argv);
    std::cout<<driver.message;
    if(driver.doStream){
        gst_init(&argc,&argv);
        TestRunner testRunner("rabbit.mp4");
        testRunner.run();
    }
    return 0;
}
