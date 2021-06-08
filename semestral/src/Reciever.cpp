//
// Created by kostdani on 5/29/21.
//

#include "Reciever.h"


Reciever::Reciever(int descriptor): Actor(descriptor) {

}

bool Reciever::multiplex(int epolld) {
    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLET;
    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}


void Reciever::onInput() {
    printf("recieve input %d\n",m_descriptor);
}

void Reciever::onError() {
    printf("recieve error\n");
}

