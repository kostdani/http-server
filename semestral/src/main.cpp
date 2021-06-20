#include <iostream>
#include "Epoller.h"
#include "Accepter.h"
#include "Counter.h"
#include "Timer.h"
#include "Sender.h"
#include "Logger.h"
#include <thread>
#include "FileContent.h"
#include "HTTPServer.h"
#include "csignal"
std::string samplerawrequest("GET / HTTP/1.0\n"
                    "Host: 127.0.0.1:8080\n\n");


int main(int argc,char **argv) {
    signal(SIGPIPE, SIG_IGN);
    if(argc!=2){
        printf("To use specify cfg file like this: ./Server config.cfg\n" );
        return 1;
    }
    std::string cfgpath(argv[1]);
    HTTPServer serv;
    printf("Starting server...\n");
    if(!serv.LoadConfig(cfgpath)|| !serv.Start()){
        printf("cant start server.\n");
        return 1;
    }
    printf("Server stopped\n");
    return 0;

}
