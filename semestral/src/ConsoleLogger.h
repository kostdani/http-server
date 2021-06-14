//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_CONSOLELOGGER_H
#define SERVER_CONSOLELOGGER_H
#include "Logger.h"

class ConsoleLogger: public Logger{
public:
    ConsoleLogger();

    void handler(std::string msg) override;
};


#endif //SERVER_CONSOLELOGGER_H
