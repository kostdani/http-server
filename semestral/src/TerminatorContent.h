//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_TERMINATORCONTENT_H
#define SERVER_TERMINATORCONTENT_H
#include "ContentGenerator.h"
/// Actor shutting down the server when getting a message
class TerminatorContent : public ContentGenerator{
public:
    TerminatorContent(bool &stopb);

    void Run(uint32_t events) override;

    void handler(HTTPRequest& msg) override;
protected:
    uint32_t TrackedEvents() const override;
    bool &m_stop;
};


#endif //SERVER_TERMINATORCONTENT_H
