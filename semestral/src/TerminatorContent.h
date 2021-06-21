//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_TERMINATORCONTENT_H
#define SERVER_TERMINATORCONTENT_H
#include "ContentGenerator.h"
/// Actor shutting down the server when getting a message
class TerminatorContent : public ContentGenerator{
public:
    /// @param stopb bool to be set true to stop server
    TerminatorContent(bool &stopb);

    void Run(uint32_t events) override;

    void handler(HTTPRequest& msg) override;
protected:
    /// Input level triggered
    uint32_t TrackedEvents() const override;
    bool &m_stop;
};


#endif //SERVER_TERMINATORCONTENT_H
