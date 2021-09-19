#include "parser.h"

Parser::Parser()
{
    std::string path=std::filesystem::current_path().parent_path().u8string()+"/src";
    config_location=path+"/config.json";
    manual=path+"/manual.txt";
}

ProgramConfig Parser::createProgramDriver(int argc, char*argv[])
{
    auto args=parseArguments(argc,argv);
    ProgramConfig config;
    auto error=args.find("error");
    if(error==args.end()){
        json=getConfigObject();
        if(config.doStream= processConfigSetupOperation(args)){
            updateConfigObject(args);
            mapJsonToConfigObject(config); 
        }
    }else{
        config.message="error "+args["error"];
    }
    return config;
}

bool Parser::processConfigSetupOperation(std::map<std::string,std::string> args){
    if(args.find("-config")!=args.end()){
        if(args.size()==1){
        for (const auto& [key, value] : json) {
        std::cout << "      "<<key << "  " << value << "\n";
    } 
        }else{
            args.erase("-config");
            updateConfigObject(args);
            saveJson(json);
        }
        return false;
    }else if(args.find("-h")!=args.end()){
        printManual();
        return false;
    }else
    return true;
}

std::map<std::string,std::string> Parser::parseArguments(int argc, char* argv[])
{
    std::map<std::string,std::string> arguments;
    std::string buffer="";
    for(int i=1;i<argc;i++){
        if(argv[i][0]=='-'){
            arguments.insert({argv[i],""});
            buffer=argv[i];
        }else{
            if(arguments.size()==0){
                std::string msg(argv[i]);
                arguments.insert({"error",msg+ " no such an argument, try gCosm -h\n"});
                return arguments;
            }else if(argv[i][0]=='-'){
                arguments.insert({argv[i],""});
                buffer=argv[i];
            }else{
                if(buffer==""){
                std::string msg(argv[i]);
                arguments.insert({"error",msg+ " wrongly passed argument\n"});
                break;
                }
                arguments[buffer]=argv[i];
                buffer="";
            }
        }
    }
    return arguments;
}

std::map<std::string,std::string> Parser::getConfigObject()
{
    std::map<std::string,std::string> json;
    std::ifstream file(config_location);
    if(file.is_open()){
        std::string current_line="";
        while(getline(file,current_line))
        {
            if(current_line!="{"&&current_line!="}")
            {
                bool isKey=true, doWrite=false;
                std::string buffer="", key="";
                for(auto it=current_line.begin();it!=current_line.end();it++){
                    if((*it)=='"'){
                        doWrite=!doWrite;
                        if(!doWrite){
                            if(isKey){
                                json[buffer]="";
                                key=buffer;
                                buffer="";
                                isKey=false;
                            }else{
                                json[key]=buffer;
                            }
                        }
                    }else{
                        if(doWrite==true){
                        buffer+=*it;
                        }
                    }
                }
            }
        }
    }
    return json;
}

void Parser::printManual(){
    std::ifstream man(manual);
    if(man.is_open()){
        std::string line;
        while(getline(man,line)){
            std::cout<<line<<std::endl;
        }
    }
    man.close();
}

void Parser::updateConfigObject(std::map<std::string,std::string> args)
{
    for(const auto&[key,value]:json){
        std::string buffer=key,command="-";
        for(auto it=buffer.begin();it!=buffer.end();it++){
            if(isupper(*it)){
                command+=tolower(*it);
            }
        }
        if(args.find(command)!=args.end()){
            json[key]=args[command];
        }
    }
}

void Parser::saveJson(std::map<std::string,std::string> jsonToSave)
{
    std::ofstream file(config_location, std::ofstream::out);
    if(file.is_open()){
        std::string buffer="";
        file<<"{\n";
        for(const auto& [key,value]:jsonToSave){
            if(buffer!=""){
                file<<buffer;
                file<<",\n";
            }
            buffer='"'+key+'"'+": "+'"'+value+'"';
        }
        file<<buffer;
        file<<"\n}"; 
    }
    file.close();
}

void Parser::mapJsonToConfigObject(ProgramConfig& config)
{
    config.ListeningPort=std::stoi(json["ListeningPort"]);
    config.SaveFile=json["SaveFile"];
    config.LoadFile=json["LoadFile"];
    config.Protocol=json["Protocol"];
    config.DoSend= (json["DoSend"]=="send"||json["DoSend"]=="Send")?true:false;
    config.AddressPath=json["AddressPath"];
    config.IpAddress=json["IpAddress"];
}