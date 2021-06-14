//
// Created by kostdani on 6/12/21.
//

#include "Logger.h"

Logger::Logger(std::ostream& out):Queuer<std::string>(),m_out(out) {}

void Logger::handler(std::string msg) {
    m_out<<msg<<std::endl;
    //std::cout<<"logger: "<<msg<<std::endl;
}