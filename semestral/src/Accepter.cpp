//
// Created by kostdani on 5/22/21.
//

#include "Accepter.h"

sockaddr_in IPv4_converter(const char * ip,int port){
    sockaddr_in res{};
    inet_pton(AF_INET, ip, &res.sin_addr);
    res.sin_family = AF_INET;
    res.sin_port = htons(port);
    return res;
}


Accepter::Accepter(Logger *logger,ContentGenerator *content,sockaddr_in addr): Actor(socket(PF_INET, SOCK_STREAM, 0)) {
    m_logger=logger;
    m_reqmanager=content;
    if (fcntl(m_descriptor, F_SETFL, fcntl(m_descriptor, F_GETFL, 0) | O_NONBLOCK) == -1)
        throw std::runtime_error("cant make sock non blocking");
    int enable = 1;
    if (setsockopt(m_descriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw std::runtime_error("Cant make socket reusable");

    if(bind(m_descriptor,(sockaddr*)&addr,sizeof(addr))==-1)
        throw std::logic_error("cant bind socket to given address");

    if(listen(m_descriptor,10)==-1)
        throw std::runtime_error("cant start listening socket");
}

Accepter::Accepter(Logger *logger,ContentGenerator *content,const char *ip, int port) : Accepter(logger,content,IPv4_converter(ip,port)){}

Reciever * Accepter::Accept() const{
    sockaddr_in addr={};
    socklen_t len=sizeof (sockaddr_in);
    int d=accept(m_descriptor,(sockaddr *)&addr,&len);
    if(d==-1)
        return nullptr;
    else
        return new Reciever(m_logger, d, addr, m_reqmanager);
}

void Accepter::Run(uint32_t events) {
    Reciever *client;
    while((client=Accept())) {
        AddActor(client);
    }
}

uint32_t Accepter::TrackedEvents() const {
    return EPOLLIN | EPOLLERR | EPOLLET;
}