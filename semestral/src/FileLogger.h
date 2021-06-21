//
// Created by kostdani on 6/15/21.
//

#ifndef SRC_FILELOGGER_H
#define SRC_FILELOGGER_H
#include "Logger.h"

/// Logger actor writes recieved logs to given file
class FileLogger: public Logger{
public:
    FileLogger(const std::string& logfilename);

    void handler(std::string& msg) override;
protected:
    std::string m_logfile;
};


#endif //SRC_FILELOGGER_H
