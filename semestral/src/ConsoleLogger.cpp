//
// Created by kostdani on 6/14/21.
//

#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger(): Logger("") {}

void ConsoleLogger::handler(std::string msg) {
    std::cout<<msg<<std::endl;
}