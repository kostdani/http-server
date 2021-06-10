//
// Created by kostdani on 5/31/21.
//

#include "Queuer.h"

Queuer::Queuer():Counter() {}

void Queuer::Push(Message *msg) {
    m_mtx.lock();
    m_queue.push(msg);
    Add(1);
    m_mtx.unlock();
}
bool Queuer::Empty() const{
    return m_queue.empty();
}
Message * Queuer::Pop() {
    Message *r=nullptr;
    m_mtx.lock();
    if(!m_queue.empty()){
        r=m_queue.front();
        m_queue.pop();
    }else{
        Reset();
    }
    m_mtx.unlock();
    return r;
}

void Queuer::onInput() {
    printf("queuer input\n");
    Message *msg;
    while((msg=Pop())){
        printf("handlong message\n");
        msghandler(msg);
    }
}


bool Queuer::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN ;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}