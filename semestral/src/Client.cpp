//
// Created by kostdani on 5/22/21.
//

#include "Client.h"

Client::Client(int descriptor, sockaddr_in addr): Queuer(){
    m_parent->AddActor(new Reciever(descriptor));
    m_parent->AddActor(new Sender (dup(descriptor)));
    m_parent->AddActor(new Timer(1));
    m_addr=addr;
}


void Client::onInput() {
    printf("cli input %d\n",m_descriptor);
    char buf[256]{};
    while(true){
        int len = read(m_descriptor, buf, 256);
        printf("len %d\n",len);
        if(len==-1){
            printf("error %d\n",errno);
            break;
        }
        std::cout.write(buf,len);
        if(len < 256) {
            break;
        }
    }
}
void Client::onError() {
    printf("cli error\n");
}

/*
bool Client::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLET;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}*/