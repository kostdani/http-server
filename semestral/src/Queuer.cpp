//
// Created by kostdani on 5/31/21.
//

#include "Queuer.h"

Queuer::Queuer():Counter() {}

void Queuer::Push(Message * msg) {
    m_mtx.lock();
    m_queue.push(msg);
    Add(1);
    m_mtx.unlock();
}

bool Queuer::Empty() const{
    return m_queue.empty();
}


Message * Queuer::Pop() {

    Message * r=0;
    m_mtx.lock();
    if(!m_queue.empty()){
        r=m_queue.front();
        m_queue.pop();
    }else{
        printf("nomoremsgs\n");
        Reset();
    }
    m_mtx.unlock();
    return r;
}

void Queuer::onInput() {
    printf("queuer input\n");
    Message * msg=0;
    while((msg=Pop())){
        printf("handling message\n");
        std::cout<<msg<<std::endl;
    }
}

bool Queuer::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLET;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}