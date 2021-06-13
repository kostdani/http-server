//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_QUEUER_H
#define SERVER_QUEUER_H
#include "Counter.h"
#include "Message.h"
#include <queue>
#include <mutex>

template <class T>
class Queuer : public Counter {
public:
    Queuer():Counter() {}
   // ~Queuer();

    void Push(T msg){
        m_mtx.lock();
        m_queue.push(msg);
        Add(1);
        m_mtx.unlock();
    }

    std::pair<T,bool> Pop(){

        std::pair<T,bool> r= {};
        m_mtx.lock();
        if(!m_queue.empty()){
            r.first=m_queue.front();
            r.second=true;
            m_queue.pop();
        }else{
            Reset();
        }
        m_mtx.unlock();
        return r;
    }

    bool Empty() const{
        return m_queue.empty();
    }

    void onInput() override{

        std::pair<T,bool> msg= {};
        while(true){
            msg=Pop();
            if(!msg.second)
                break;
            handler(msg.first);
            //std::cout<<msg<<std::endl;
        }
    }

    virtual void handler(T msg){
        //std::cout<<msg->msg<<std::endl;
    }

    bool multiplex(int epolld) override{

        epoll_event ev{};
        ev.data.ptr = this;
        ev.events = EPOLLIN | EPOLLET;

        return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

    }
protected:
    std::queue<T> m_queue;
    std::mutex m_mtx;
};


#endif //SERVER_QUEUER_H
