//
// Created by kostdani on 6/15/21.
//

#ifndef SRC_FILELOGGER_H
#define SRC_FILELOGGER_H
#include "Logger.h"

class FileLogger: public Logger{
public:
    FileLogger(std::string logfilename);

    void handler(std::string msg) override;
protected:
    std::string m_logfile;
};


#endif //SRC_FILELOGGER_H
