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
    if(!serv.LoadConfig(cfgpath)){
        std::cout<<"Server has not started because something is wrong with config."<<std::endl;
        return 1;
    }
    std::cout<<"Server has started."<<std::endl;
    serv.Start();
    std::cout<<"Server has stopped."<<std::endl;
    return 0;

}
