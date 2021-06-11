//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_ACCEPTER_H
#define SERVER_ACCEPTER_H
#include "Actor.h"
#include "Reciever.h"
#include "Client.h"
#include <sys/socket.h>
#include <arpa/inet.h>


class Accepter : public Actor{
public:
    Accepter(sockaddr_in addr);

    Accepter(const char * ip="127.0.0.1",int port=80);

    void onInput() override;

    Client *Accept();

protected:
    bool multiplex(int epolld) override;
};


#endif //SERVER_ACCEPTER_H
