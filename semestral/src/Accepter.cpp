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


Accepter::Accepter(sockaddr_in addr): Actor(socket(PF_INET, SOCK_STREAM, 0)) {

    int status = fcntl(m_descriptor, F_SETFL, fcntl(m_descriptor, F_GETFL, 0) | O_NONBLOCK);
    if (status == -1){
        throw "cant make sock non blocking\n";
    }

    if(!Check()){
        throw "cant create server socket\n";
    }

    if(bind(m_descriptor,(sockaddr*)&addr,sizeof(addr))==-1) {
        throw "cant bind\n";
    }

    if(listen(m_descriptor,10)==-1) {
        throw "cant listen\n";
    }
}

Accepter::Accepter(const char *ip, int port) : Accepter(IPv4_converter(ip,port)){};

Client * Accepter::Accept() {
    sockaddr_in addr;
    socklen_t len;
    int d= accept(m_descriptor,0,0);
    if(d==-1)
        return nullptr;
    else
        return new Client(d,addr);
}

void Accepter::onInput() {
    printf("new clients available\n");
    while(true) {
        printf("here\n");
        Client *newcli = Accept();
        if(!newcli)
            break;
        printf("addng new cli\n");
        Message *sm=new Message();
        *sm={Message::msg_type::SETTINGS,""};
        newcli->Push(sm);
        AddActor(newcli);
    }

}



bool Accepter::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLERR | EPOLLET;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}