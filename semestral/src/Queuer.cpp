//
// Created by kostdani on 5/31/21.
//

#include "Queuer.h"

Queuer::Queuer():Counter() {}

void Queuer::Put(Message *msg) {
    m_mtx.lock();
    m_queue.push(msg);
    Add(1);
    m_mtx.unlock();
}
bool Queuer::Empty() const{
    return m_queue.empty();
}
Message * Queuer::Get() {
    auto m= m_queue.front();
    m_queue.pop();
    return m;
}

void Queuer::onInput() {
    printf("queuer input\n");
    while(true){
        m_mtx.lock();
        if(m_queue.empty()){
            Reset();
            m_mtx.unlock();
            break;
        }
        auto m=m_queue.front();
        m_queue.pop();
        m_mtx.unlock();
        
        //
        msghandler(m);
    }
}


bool Queuer::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN ;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}