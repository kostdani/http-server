//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_HTTPSERVER_H
#define SERVER_HTTPSERVER_H
#include "Epoller.h"
#include "Counter.h"
#include "Accepter.h"
#include "Logger.h"
#include "FileLogger.h"
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
    /// Read parse and load config from file
    /// @param cfgpath path to config file
    /// returns true if config was loaded successfully
    bool LoadConfig(const std::string& cfgpath);
    /// Starts the server
    /// @returns true if server have started
    bool Start();

protected:
    /// Function for threads
    /// @param threadi thread number
    void threadfunction(int threadi);
    /// Load threads configuration
    bool LoadThreads(const std::map<std::string,std::string> &cfgmap);
    /// Load log configuration
    bool LoadLogfile(const std::map<std::string,std::string> &cfgmap);
    /// Load tcp listen configuration
    bool LoadListen(const std::map<std::string,std::string> &cfgmap);
    /// Load virtual filesystem map configuration
    bool LoadVirtualfs(const std::map<std::string,std::string> &cfgmap);

    /// The logger used to store logs
    Logger *m_logger=nullptr;
    /// Threads contiunue running while this is true
    bool m_stop=true;
    /// Main event poll multiplexing other actors
    Epoller m_epoller;
    /// Vector of working threads
    std::vector<std::thread> m_threads;
    /// Number of threads
    int thrn=1;
    // Main content generator
    ContentGenerator *m_content= nullptr;
};


#endif //SERVER_HTTPSERVER_H
