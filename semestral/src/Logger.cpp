//
// Created by kostdani on 6/12/21.
//

#include "Logger.h"

Logger::Logger(std::string logfilename):Queuer<std::string>() {

    std::ofstream out;
    out.open(logfilename);
    if(out.is_open()) {
        m_logfile = logfilename;
    }else{
        printf("cantopenfile\n");
    }


}
void Logger::handler(std::string msg) {
    std::ofstream out;
    out.open(m_logfile, std::ios::app);
    if(out.is_open()){
        out<<msg;
        std::cout<<"logger: "<<msg<<std::endl;
        out.close();
    }
}