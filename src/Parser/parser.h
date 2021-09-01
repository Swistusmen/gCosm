#include "ProgramConfig.h"
#include <map>
#include <fstream>
#include <filesystem>
#include <iostream>

class Parser{
    public:
        Parser();
        ProgramConfig createProgramDriver(int argc, char*argv[]);

    private:
        void mapJsonToConfigObject(ProgramConfig& config);
        void updateConfigObject(std::map<std::string,std::string> args);
        void saveJson(std::map<std::string,std::string> );
        void printManual();
        bool processConfigSetupOperation(std::map<std::string,std::string> args);

        std::map<std::string,std::string> getConfigObject(); 
        std::map<std::string,std::string> parseArguments(int argc,char* argv[]);
    private:
        std::string config_location=""; 
        std::string manual="";   
        std::map<std::string,std::string> json;
};