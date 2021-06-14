//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H
#include "Queuer.h"
#include <iostream>
class Logger: public Queuer< std::string >{
public:
    Logger(std::ostream& out);

    void handler(std::string msg) override;
protected:
    std::ostream & m_out;
};


#endif //SERVER_LOGGER_H
