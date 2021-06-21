//
// Created by kostdani on 5/29/21.
//

#include "Reciever.h"

const int BUFSIZE=4096;

Reciever::Reciever(Logger *l, int descriptor, sockaddr_in addr, ContentGenerator *generator) : Actor(descriptor), m_addr(addr) {
    m_logger=l;
    m_reqmanager=generator;
    m_stream= fdopen(m_descriptor,"r");
}

Reciever::~Reciever()  {
    if(m_stream)
        pclose(m_stream);
    m_stream= nullptr;
    Close();
}

uint32_t Reciever::TrackedEvents() const{
    return EPOLLIN | EPOLLET;
}


void Reciever::Run(uint32_t events) {
    if(events&(EPOLLERR|EPOLLHUP|EPOLLRDHUP)){
        throw std::runtime_error("");
    }
    if(!m_sender){
        m_sender=new Sender(dup(m_descriptor));
        AddActor(m_sender);
    }

    std::string request;
    std::string line;
    while((line=GetLine()).size()>2){
        request+=line;
    }
    if(!request.empty()) {
        HTTPRequest req(m_logger, m_sender, GetIP(), request);
        m_sender->m_awaited++;
        m_reqmanager->Push(req);
    }
}

std::string Reciever::GetLine() {
    char buffer[BUFSIZE]{};
    std::string line;
    if(m_stream){
        while(fgets(buffer,BUFSIZE,m_stream) && strlen(buffer)==BUFSIZE){
            line+=buffer;
        }
        line+=buffer;
    }
    return line;
}

std::string Reciever::GetIP() const {
    return  inet_ntoa(m_addr.sin_addr);
}
