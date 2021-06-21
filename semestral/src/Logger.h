//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H
#include "Queuer.h"
#include <iostream>
#include <fstream>

/// Logger actor writes recieved logs to stdout
class Logger: public Queuer< std::string >{
public:
    Logger();

    void handler(std::string& msg) override;
};


#endif //SERVER_LOGGER_H
