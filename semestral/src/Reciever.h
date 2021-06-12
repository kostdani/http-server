//
// Created by kostdani on 5/29/21.
//

#ifndef SERVER_RECIEVER_H
#define SERVER_RECIEVER_H
#include "Actor.h"
#include "Queuer.h"

class Reciever : public Actor{
public:
    Reciever(int descriptor,Queuer<Message *> *q);

    void onInput() override;

    void onError() override;

protected:
    Queuer<Message *> *m_q;
    std::string m_str="";
    bool multiplex(int epolld) override;
};


#endif //SERVER_RECIEVER_H
