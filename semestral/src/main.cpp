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

std::string samplerawrequest("GET / HTTP/1.0\n"
                    "Host: 127.0.0.1:8080\n\n");


int main() {
    HTTPServer serv;
    printf("Starting server...\n");
    if(!serv.LoadConfig("server.cfg")|| !serv.Start()){
        printf("cant start server.\n");
        return 1;
    }

    std::cout << "Press enter to stop server" << std::endl;
    std::cin.ignore();
    serv.Stop();
    return 0;
}
