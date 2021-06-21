//
// Created by kostdani on 5/22/21.
//

#include "Epoller.h"

Epoller::Epoller(): Actor(epoll_create(666)) {}

Epoller::~Epoller() {
    Close();
    for(auto ptr:m_actors){
        delete ptr;
    }
}

epoll_event Epoller::GetEvent() {
    struct epoll_event ev{};
    epoll_wait(m_descriptor,&ev,1,-1);
    return ev;
}

bool Epoller::AddActor(Actor *newActor) {
    if (newActor && newActor->Check()) {
        newActor->m_parent = this;
        if(newActor->multiplex(m_descriptor)){
            m_actors.insert(newActor);
            return true;
        }
    }
    return false;
}


bool Epoller::RmActor(Actor *actor) {
    auto it=m_actors.find(actor);
    if(it==m_actors.end())
        return false;
    delete actor;
    m_actors.erase(it);
    return true;
}

void Epoller::Run(uint32_t events) {

}


uint32_t Epoller::TrackedEvents() const {
    return EPOLLIN;
}