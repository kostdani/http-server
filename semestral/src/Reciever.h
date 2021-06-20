//
// Created by kostdani on 5/29/21.
//

#ifndef SERVER_RECIEVER_H
#define SERVER_RECIEVER_H
#include "Actor.h"
#include "Queuer.h"
#include "Logger.h"
#include "Sender.h"
#include "HTTPRequest.h"
#include <netdb.h>
#include <arpa/inet.h>
#include "ContentGenerator.h"

/// Actor recieving data from tcp socket
class Reciever : public Actor{
public:
    Reciever(Logger *l, int descriptor, sockaddr_in addr, ContentGenerator *generator);
    /// Returns client IP in string form
    std::string GetIP() const;

    void Run(uint32_t events) override;

protected:
    Sender *m_sender=nullptr;
    Logger *m_logger=nullptr;
    sockaddr_in m_addr;
    std::string m_str;
    uint32_t TrackedEvents() const override;
    ContentGenerator *m_reqmanager;
};


#endif //SERVER_RECIEVER_H
