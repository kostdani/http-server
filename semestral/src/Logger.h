//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H
#include "Queuer.h"
#include <fstream>
class Logger: public Queuer< std::string >{
public:
    Logger(std::string logfilename);

    void handler(std::string msg) override;
protected:
    std::string m_logfile;
};


#endif //SERVER_LOGGER_H
