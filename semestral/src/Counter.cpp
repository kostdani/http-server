//
// Created by kostdani on 5/28/21.
//

#include "Counter.h"

Counter::Counter():Actor(eventfd(0,EFD_NONBLOCK)) {}

void Counter::Add(eventfd_t x) {
    if(Check())
        eventfd_write(m_descriptor,x);
}

void Counter::Reset() {
    eventfd_t i=0;
    if(Check())
        eventfd_read(m_descriptor,&i);
}

uint32_t Counter::TrackedEvents() const {
    return EPOLLIN;
}