//
// Created by kostdani on 6/12/21.
//

#include "Logger.h"

Logger::Logger():Queuer<std::string>(){}

void Logger::handler(std::string& msg) {
    std::cout<<msg<<std::endl;
}