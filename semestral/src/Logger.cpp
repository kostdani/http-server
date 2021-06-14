//
// Created by kostdani on 6/12/21.
//

#include "Logger.h"

Logger::Logger(std::string logfilename):Queuer<std::string>(){
    m_logfile=logfilename;
}

void Logger::handler(std::string msg) {

    std::ofstream file(m_logfile,std::ios::app);
    if(file.is_open()){
        file<<msg<<std::endl;
    }
}