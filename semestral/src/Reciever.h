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
class Reciever : public Actor{
public:
    Reciever(Logger *l, int descriptor, sockaddr_in addr, ContentGenerator *generator);

    std::string GetIP();

    void onInput(int threadi) override;

    void onError(int threadi) override;

protected:
    Sender *m_sender=0;
    sockaddr_in m_addr;
    Queuer<Message *> *m_q;
    std::string m_str="";
    Logger *m_logger=0;
    bool multiplex(int epolld) override;
    ContentGenerator *m_reqmanager;
};


#endif //SERVER_RECIEVER_H
