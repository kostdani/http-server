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

    void Run(uint32_t events) override;

    void handler(HTTPRequest& msg) override{}

protected:
    uint32_t TrackedEvents() const override;
    bool &m_stop;
    std::vector<std::thread> &m_threads;
};


#endif //SERVER_TERMINATORCONTENT_H
