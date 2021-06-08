//
// Created by kostdani on 5/22/21.
//

#include "Epoller.h"

Epoller::Epoller(): Actor(epoll_create(666)) {}

Epoller::~Epoller() {
    for(auto ptr:m_actors){
        delete ptr;
    }
}

epoll_event Epoller::getEvent() {
    struct epoll_event ev;
    epoll_wait(m_descriptor,&ev,1,-1);
    return ev;
}

bool Epoller::AddActor(Actor *newActor) {
    if (newActor && newActor->Check()) {
        newActor->m_parent = this;
        //ev.events = newActor->m_events;
        /*
        epoll_event ev{};
        ev.data.ptr = newActor;
        ev.events = newActor->flags();
        if (epoll_ctl(m_descriptor, EPOLL_CTL_ADD, newActor->m_descriptor, &ev) == 0) {
            m_actors.insert(newActor);
            return true;
        }*/
        if(newActor->multiplex(m_descriptor)){
            m_actors.insert(newActor);
            return true;
        }
    }
    return false;
}



