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

epoll_event Epoller::GetEvent() {
    struct epoll_event ev;
    epoll_wait(m_descriptor,&ev,1,-1);
    return ev;
}

bool Epoller::AddActor(Actor *newActor) {
    if (newActor && newActor->Check()) {
        std::lock_guard<std::mutex> guard(m_mtx);
        newActor->m_parent = this;
        if(newActor->multiplex(m_descriptor)){
            m_actors.insert(newActor);
            return true;
        }
    }
    return false;
}


void Epoller::Run(int threadi) {

}

void Epoller::Error(int threadi) {

}

uint32_t Epoller::TrackedEvents() const {
    return EPOLLIN;
}