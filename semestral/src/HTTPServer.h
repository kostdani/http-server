//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_HTTPSERVER_H
#define SERVER_HTTPSERVER_H
#include "Epoller.h"
#include "Counter.h"
#include "Accepter.h"
#include "Logger.h"
#include <thread>
#include <vector>
#include <fstream>
class HTTPServer {
public:
    // Constructor
    HTTPServer();
    // Load Config file
    bool Config(std::ifstream cfg_file);
    // Starts the server
    bool Start(int thrn);
    // Stops the server
    bool Stop();

    void threadfunction();

protected:
    Logger *m_logger=0;
    bool m_stop=true;
    Counter *m_stopper= nullptr;
    Epoller m_epoller;
    std::vector<std::thread> m_threads;
};


#endif //SERVER_HTTPSERVER_H
