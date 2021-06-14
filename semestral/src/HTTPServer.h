//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_HTTPSERVER_H
#define SERVER_HTTPSERVER_H
#include "Epoller.h"
#include "Counter.h"
#include "Accepter.h"
#include "Logger.h"
#include "ContentGenerator.h"
#include "FileContent.h"
#include "TerminatorContent.h"
#include "DirectoryContent.h"
#include "VirtualDirrectoryContent.h"
#include <thread>
#include <vector>
#include <fstream>
#include <map>
class HTTPServer {
public:
    // Constructor
    HTTPServer();
    // Load Config file
    bool LoadConfig(std::string filename);
    // Starts the server
    bool Start();
    // Stops the server
    bool Stop();

    void threadfunction(int threadi);

protected:
    bool LoadThreads(std::map<std::string,std::string> &cfgmap);
    bool LoadLogfile(std::map<std::string,std::string> &cfgmap);
    bool LoadListen(std::map<std::string,std::string> &cfgmap);
    bool LoadVirtualfs(std::map<std::string,std::string> &cfgmap);
    Logger *m_logger=nullptr;
    bool m_stop=true;
    Counter *m_stopper= nullptr;
    Epoller m_epoller;
    std::vector<std::thread> m_threads;
    int thrn=1;

    ContentGenerator *m_content= nullptr;
};


#endif //SERVER_HTTPSERVER_H
