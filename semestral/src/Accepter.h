//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_ACCEPTER_H
#define SERVER_ACCEPTER_H
#include "Actor.h"
#include "Reciever.h"
#include "Logger.h"
#include <sys/socket.h>
#include <arpa/inet.h>

/// Actor that accept new clients
///
/// This actor estabilishes connection with client and creates Reciever actor
class Accepter : public Actor{
public:
    /// Basic constructor
    /// @param logger Logger which will be used to log
    /// @param content Content generator which will be used by created recievers
    Accepter(Logger *logger,ContentGenerator *content,sockaddr_in addr);

    /// Constructor with string
    /// Converts string ip to sockaddr_in and calls basic constructor
    /// @see Accepter(Logger *,ContentGenerator *,sockaddr_in)
    Accepter(Logger *logger,ContentGenerator *content,const char * ip="0.0.0.0",int port=8080);

    void Run(int threadi) override;

    void Error(int threadi) override;
    /// Accept new connection
    /// Tries to estabilish connection with new client
    /// @returns pointer to new Reciver if accept was sucessful otherwise returns nullptr
    Reciever *Accept() const;

    bool multiplex(int epolld) override;
protected:
    Logger *m_logger=0;
    ContentGenerator *m_reqmanager;
};


#endif //SERVER_ACCEPTER_H
