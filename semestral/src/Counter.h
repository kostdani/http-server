//
// Created by kostdani on 5/28/21.
//

#ifndef SERVER_COUNTER_H
#define SERVER_COUNTER_H
#include "Actor.h"
#include <sys/eventfd.h>

class Counter: public Actor {
public:
    Counter();

    void Add(uint32_t x);

    void Reset();

protected:
    bool multiplex(int epolld) override;
};


#endif //SERVER_COUNTER_H
