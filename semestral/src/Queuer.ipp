//
// Created by kostdani on 5/31/21.
//
#ifdef SERVER_QUEUER_H
//Class definition goes here


template <class T>
Queuer<T>::Queuer():Counter() {}

template <class T>
void Queuer<T>::Push(const T& msg){
    m_queue.push(msg);
    Add(1);
}

template <class T>
std::pair<T,bool> Queuer<T>::Pop(){
    std::pair<T,bool> r= {};
    if(!m_queue.empty()){
        r.first=m_queue.front();
        r.second=true;
        m_queue.pop();
    }else{
        Reset();
    }
    return r;
}

template <class T>
void Queuer<T>::Run(uint32_t events){
    std::pair<T,bool> msg= {};
    while(true){
        msg=Pop();
        if(!msg.second)
            break;
        handler(msg.first);
    }
}
template <class T>
uint32_t Queuer<T>::TrackedEvents() const {
    return EPOLLIN | EPOLLET;
}

#endif