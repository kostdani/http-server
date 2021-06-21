#include <iostream>
#include <thread>
#include "HTTPServer.h"
#include "csignal"


int main(int argc,char **argv) {
    signal(SIGPIPE, SIG_IGN);
    if(argc!=2){
        std::cout<<"To use specify cfg file like this: ./Server config.cfg"<<std::endl;
        return 1;
    }
    std::string cfgpath(argv[1]);
    HTTPServer serv;
    std::cout<<"Starting server."<<std::endl;
    if(!serv.LoadConfig(cfgpath)||!serv.Start()){
        std::cout<<"Cant start server."<<std::endl;
        return 1;
    }
    std::cout<<"Server stopped"<<std::endl;
    return 0;

}
