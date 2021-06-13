//
// Created by kostdani on 6/8/21.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H
#include "Queuer.h"

class Sender: public Queuer<std::string >{
public:
    Sender(int descriptor);



    void onInput() override;
    void onOutput() override;

    void handler(std::string msg) override;

    bool multiplex(int epolld) override;
protected:
    int m_socketfd=-1;
    std::string last;
    int n=0;

};


#endif //SERVER_SENDER_H
