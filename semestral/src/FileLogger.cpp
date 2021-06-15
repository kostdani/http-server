//
// Created by kostdani on 6/15/21.
//

#include "FileLogger.h"

FileLogger::FileLogger(std::string logfilename):Logger(){
    m_logfile=logfilename;
}

void FileLogger::handler(std::string msg) {
    std::ofstream file(m_logfile,std::ios::app);
    if(file.is_open()){
        file<<msg<<std::endl;
    }
}