//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_HTTPSERVER_H
#define SERVER_HTTPSERVER_H
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
    bool Start();
    // Stops the server
    bool Stop();


protected:
    std::vector<std::thread> m_threads;
};


#endif //SERVER_HTTPSERVER_H
