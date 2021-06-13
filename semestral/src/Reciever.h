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
#include "FileContent.h"
#include <netdb.h>
class Reciever : public Actor{
public:
    Reciever(Logger *l,int descriptor,sockaddr_in addr);

    void onInput() override;

    void onError() override;

protected:
    Sender *m_sender=0;
    sockaddr_in m_addr;
    Queuer<Message *> *m_q;
    std::string m_str="";
    Logger *m_logger=0;
    bool multiplex(int epolld) override;
};


#endif //SERVER_RECIEVER_H
