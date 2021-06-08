//
// Created by kostdani on 5/28/21.
//

#include "Counter.h"

Counter::Counter():Actor(eventfd(0,EFD_NONBLOCK)) {}

void Counter::Add(uint32_t x) {
    if(Check())
        eventfd_write(m_descriptor,x);
}

void Counter::Reset() {
    if(Check())
        eventfd_read(m_descriptor,0);
}



bool Counter::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN ;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}