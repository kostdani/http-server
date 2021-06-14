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
        m_mtx.lock();
        newActor->m_parent = this;
        if(newActor->multiplex(m_descriptor)){
            m_actors.insert(newActor);
            m_mtx.unlock();
            return true;
        }
        m_mtx.unlock();
    }
    return false;
}



