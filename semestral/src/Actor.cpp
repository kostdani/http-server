//
// Created by kostdani on 5/22/21.
//

#include "Actor.h"

Actor::Actor(int descriptor){
    m_descriptor=descriptor;

}

bool Actor::Check() {
    return m_descriptor!=-1;
}

Actor::~Actor() {
    std::cout<<"desctruct\n";
    if(Check())
        close(m_descriptor);
}

bool Actor::AddActor(Actor *newActor) {
    if(m_parent)
        return m_parent->AddActor(newActor);
    return false;
}

void Actor::onInput() {
    printf("basicinput\n");
}
void Actor::onOutput() {
    printf("basicoutput\n");
}
void Actor::onError() {
    printf("basicerror\n");
}


bool Actor::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}
