//
// Created by kostdani on 6/8/21.
//

#include "Sender.h"

Sender::Sender(int descriptor) :Queuer(){
    m_socketfd=descriptor;
}

bool Sender::multiplex(int epolld) {
    Queuer::multiplex(epolld);
    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLOUT | EPOLLET;
    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_socketfd, &ev) == 0;

}

void Sender::onInput() {
    if(last.length()-n>=0){
        int r=write(m_socketfd,last.c_str()+n,last.length()-n);
        if(r==-1){
            printf("error %d",errno);
            return;
        }else if(r<last.length()-n){
            n+=r;
            return;
        }else{
            last="";
            n=0;
        }
    }

    std::pair<std::string,bool> msg= {};
    while(true){
        msg=Pop();
        if(!msg.second)
            break;
        handler(msg.first);
        if(!last.empty()){
            break;
        }
        //std::cout<<msg<<std::endl;
    }

}

void Sender::onOutput() {
    onInput();
}

void Sender::handler(std::string msg) {
    n=write(m_socketfd,msg.c_str(),msg.length());
    if(n==-1){
        printf("error %d",errno);
        return;
    }else if(n<msg.length()){
        last=msg;
    }else{
        n=0;
    }
}

