//
// Created by kostdani on 5/31/21.
//
#ifdef SERVER_QUEUER_H
//Class definition goes here


template <class T>
Queuer<T>::Queuer():Counter() {}

template <class T>
void Queuer<T>::Push(const T& msg){
    m_mtx.lock();
    m_queue.push(msg);
    Add(1);
    m_mtx.unlock();
}

template <class T>
std::pair<T,bool> Queuer<T>::Pop(){

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

template <class T>
void Queuer<T>::Run(int threadi){
    std::pair<T,bool> msg= {};
    while(true){
        msg=Pop();
        if(!msg.second)
            break;
        handler(msg.first);
    }
}
template <class T>
void Queuer<T>::Error(int threadi){
}


template <class T>
bool Queuer<T>::multiplex(int epolld){

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLET;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;
}

#endif