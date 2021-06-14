//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_TERMINATORCONTENT_H
#define SERVER_TERMINATORCONTENT_H
#include "ContentGenerator.h"
#include <thread>
class TerminatorContent : public ContentGenerator{
public:
    TerminatorContent(bool &stopb,std::vector<std::thread> &thrvec);


    void handler(HTTPRequest msg) override;
private:
    std::string m_filename;
};


#endif //SERVER_TERMINATORCONTENT_H
