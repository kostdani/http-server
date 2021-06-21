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
#include "ScriptContent.h"
#include "ContentGenerator.h"
#include "FileContent.h"
#include "TerminatorContent.h"
#include "DirectoryContent.h"
#include "VirtualDirrectoryContent.h"
#include <vector>
#include <fstream>
#include <map>
/// Main class implemeting loading config and starting server
class HTTPServer {
public:
    // Constructor
    HTTPServer()=default;
    /// Read parse and load config from file
    /// @param cfgpath path to config file
    /// returns true if config was loaded successfully
    bool LoadConfig(const std::string& cfgpath);
    /// Starts the server
    /// IF start was succesful the call is blocking and return true only when server is shut down
    bool Start();
private:
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
    // Main content generator
    ContentGenerator *m_content= nullptr;
};


#endif //SERVER_HTTPSERVER_H
