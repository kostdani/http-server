//
// Created by kostdani on 6/8/21.
//

#include "Sender.h"

Sender::Sender(int descriptor) :Queuer(){
    m_socketfd=descriptor;
}

bool Sender::multiplex(int epolld) {
    Queuer::multiplex(epolld);
    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLOUT | EPOLLET;
    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_socketfd, &ev) == 0;

}