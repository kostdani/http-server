//
// Created by kostdani on 5/22/21.
//

#include "Actor.h"

Actor::Actor(int descriptor){
    m_descriptor=descriptor;
}

bool Actor::Check() const{
    return m_descriptor!=-1;
}

Actor::~Actor() {
    Close();
}
void Actor::Close() {
    if(Check())
        close(m_descriptor);
    m_descriptor=-1;
}
bool Actor::AddActor(Actor *newActor) {
    if(m_parent)
        return m_parent->AddActor(newActor);
    return false;
}

bool Actor::multiplex(int epolld){

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = TrackedEvents();

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;
}
