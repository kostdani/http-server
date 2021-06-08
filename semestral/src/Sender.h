//
// Created by kostdani on 6/8/21.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H
#include "Queuer.h"

class Sender: public Queuer {
public:
    Sender(int descriptor);


    void onInput() override;

    void onOutput() override;

    void onError() override;

protected:
    int m_socketfd=-1;

    bool multiplex(int epolld) override;
};


void Sender::onInput() {
    printf("sender input %d\n",m_descriptor);
}
void Sender::onOutput() {
    printf("sender out %d\n",m_descriptor);
}

void Sender::onError() {
    printf("sender error\n");
}



#endif //SERVER_SENDER_H
