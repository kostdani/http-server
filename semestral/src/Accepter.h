//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_ACCEPTER_H
#define SERVER_ACCEPTER_H
#include "Actor.h"
#include "Reciever.h"
#include "Client.h"
#include "Logger.h"
#include <sys/socket.h>
#include <arpa/inet.h>


class Accepter : public Actor{
public:
    Accepter(Logger *l,ContentGenerator *content,sockaddr_in addr);

    Accepter(Logger *l,ContentGenerator *content,const char * ip="127.0.0.1",int port=80);

    void onInput(int threadi) override;

    Reciever *Accept();

    bool multiplex(int epolld) override;
protected:
    Logger *m_logger=0;
    ContentGenerator *m_reqmanager;
};


#endif //SERVER_ACCEPTER_H
