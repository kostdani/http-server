//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H
#include "Queuer.h"
#include "Reciever.h"
#include "Sender.h"
#include "Timer.h"
#include <sys/socket.h>
#include <arpa/inet.h>

class Client : public Queuer {
public:
    Client(int descriptor, sockaddr_in addr);


    void onInput() override;

    void onError() override;

protected:
    bool multiplex(int epolld) override;
    sockaddr_in m_addr;
};


#endif //SERVER_CLIENT_H
