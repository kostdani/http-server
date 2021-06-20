//
// Created by kostdani on 6/8/21.
//

#include "Sender.h"

Sender::Sender(int descriptor) :Queuer(){
    m_socketfd=descriptor;
    awaitedmsgs=0;
}

uint32_t Sender::TrackedEvents() const {
    return EPOLLOUT|EPOLLET;
}

bool Sender::multiplex(int epolld) {
    epoll_event ev1{};
    ev1.data.ptr = this;
    ev1.events = Queuer::TrackedEvents();
    epoll_event ev2{};
    ev2.data.ptr = this;
    ev2.events = Sender::TrackedEvents();
    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev1)==0 && epoll_ctl(epolld, EPOLL_CTL_ADD, m_socketfd, &ev2) == 0;
}

void Sender::Run(int theardi) {
    if(last.length()-n>=0){
        ssize_t r=write(m_socketfd,last.c_str()+n,last.length()-n);
        if(r==-1){
            printf("error %d",errno);
            return;
        }else if(r<(ssize_t)last.length()-n){
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

void Sender::Error(int threadi) {
    printf("finishing sender\n");
    m_finishing=true;
}

void Sender::handler(std::string& msg) {
    if(m_finishing){
        awaitedmsgs--;
        if(awaitedmsgs==0){
            printf("killing sender\n");
            //RmActor(this);
        }
        return;
    }

    n=write(m_socketfd,msg.c_str(),msg.length());
    if(n==-1){
        printf("error %d",errno);
        return;
    }else if(n<(ssize_t)msg.length()){
        last=msg;
    }else{
        n=0;
    }
}

