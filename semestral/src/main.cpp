#include <iostream>
#include <thread>
#include "HTTPServer.h"
#include "csignal"


int main(int argc,char **argv) {
    signal(SIGPIPE, SIG_IGN);
    if(argc!=2){
        std::cout<<"To start server, specify cfg file like this: ./kostdani config.cfg"<<std::endl;
        return 1;
    }
    std::string cfgpath(argv[1]);
    HTTPServer serv;
    std::cout<<"Starting server."<<std::endl;
    if(!serv.LoadConfig(cfgpath)){
        std::cout<<"Wrong config."<<std::endl;
        return 1;
    }
    serv.Start();
    std::cout<<"Server stopped."<<std::endl;
    return 0;

}
