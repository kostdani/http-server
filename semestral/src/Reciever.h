//
// Created by kostdani on 5/29/21.
//

#ifndef SERVER_RECIEVER_H
#define SERVER_RECIEVER_H
#include "Actor.h"
#include "Logger.h"
#include "Sender.h"
#include "ContentGenerator.h"
#include "HTTPRequest.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <array>
#include <cstring>

/// Actor recieving data from tcp socket
class Reciever : public Actor{
public:
    Reciever(Logger *l, int descriptor, sockaddr_in addr, ContentGenerator *generator);

    ~Reciever() override;

    void Run(uint32_t events) override;
protected:
    /// Returns client IP in string form
    std::string GetIP() const;
    /// Get next line from socket
    std::string GetLine();
    /// Client's address
    sockaddr_in m_addr;
    /// Input, edge triggered
    uint32_t TrackedEvents() const override;
    /// Main content generator for requests
    ContentGenerator *m_reqmanager;

    Sender *m_sender=nullptr;
    Logger *m_logger=nullptr;
    /// For buffered reading
    FILE *m_stream;
};


#endif //SERVER_RECIEVER_H
