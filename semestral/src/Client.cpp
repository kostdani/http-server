//
// Created by kostdani on 5/22/21.
//

#include "Client.h"

Client::Client(int descriptor, sockaddr_in addr): Queuer(){
    m_clientfd=descriptor;
    m_addr=addr;
}

void Client::handler(Message *msg) {
    printf("client handler\n");
    if(msg->type==Message::msg_type::BYTEARRAY){
        std::cout<<msg->msg;
    }else if(msg->type==Message::msg_type::SETTINGS){
        printf("clisetup\n");
       // m_recv=new Reciever(m_clientfd,this);
        AddActor(m_recv);
    }else{
        printf("errormsg\n");
    }
}

/*
bool Client::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLET;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}*/