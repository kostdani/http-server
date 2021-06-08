//
// Created by kostdani on 5/29/21.
//

#ifndef SERVER_RECIEVER_H
#define SERVER_RECIEVER_H
#include "Actor.h"


class Reciever : public Actor{
public:
    Reciever(int descriptor);

    void onInput() override;

    void onError() override;

protected:
    bool multiplex(int epolld) override;
};


#endif //SERVER_RECIEVER_H
