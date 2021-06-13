//
// Created by kostdani on 5/22/21.
//

#include "Accepter.h"

sockaddr_in IPv4_converter(const char * ip,int port){
    sockaddr_in res;
    if (inet_pton(AF_INET, ip, &res.sin_addr) <= 0)
    {
        throw "error: cant convert address\n";
    }
    res.sin_family = AF_INET;
    res.sin_port = htons(port);
    return res;
}


Accepter::Accepter(Logger *l,sockaddr_in addr): Actor(socket(PF_INET, SOCK_STREAM, 0)) {
    m_logger=l;
    if(!l){
        throw "no logger\n";
    }
    int status = fcntl(m_descriptor, F_SETFL, fcntl(m_descriptor, F_GETFL, 0) | O_NONBLOCK);
    if (status == -1){
        m_logger->Push("cant make sock non blocking");
    }
    int enable = 1;
    if (setsockopt(m_descriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        m_logger->Push("Cant make socket reusable");

    if(!Check()){
        m_logger->Push( "cant create server socket");
    }

    if(bind(m_descriptor,(sockaddr*)&addr,sizeof(addr))==-1) {
        m_logger->Push( "cant bind");
    }

    if(listen(m_descriptor,10)==-1) {
        m_logger->Push( "cant listen");
    }
}

Accepter::Accepter(Logger *l,const char *ip, int port) : Accepter(l,IPv4_converter(ip,port)){};

Reciever * Accepter::Accept() {
    sockaddr_in addr;
    socklen_t len;
    int d= accept(m_descriptor,(sockaddr *)&addr,&len);
    if(d==-1)
        return nullptr;
    else
        return new Reciever(m_logger,d,addr);
}

void Accepter::onInput() {
    printf("new clients available\n");
    while(true) {
        printf("here\n");
        Reciever *newcli = Accept();
        if(!newcli)
            break;
        printf("addng new cli\n");
        AddActor(newcli);
    }

}



bool Accepter::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLERR | EPOLLET;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}