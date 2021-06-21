//
// Created by kostdani on 5/29/21.
//

#include "Reciever.h"


Reciever::Reciever(Logger *l, int descriptor, sockaddr_in addr, ContentGenerator *generator) : Actor(descriptor) {
    m_logger=l;
    m_reqmanager=generator;
    m_addr=addr;
}

uint32_t Reciever::TrackedEvents() const{
    return EPOLLIN | EPOLLET;
}


void Reciever::Run(uint32_t events) {
    if(events&(EPOLLERR|EPOLLHUP|EPOLLRDHUP)){
        throw this;
    }
    if(!m_sender){
        m_sender=new Sender(dup(m_descriptor));
        AddActor(m_sender);
    }
    char buf[4096]{};
    while(true){
        int len = read(m_descriptor, buf, 4096);
        if(len==-1){
            throw this;
        }
        int s=0;
        for (int i=s; i < len; ++i) {
            if(buf[i]=='\n'&& i+1<len && buf[i+1]=='\r'){
                m_str.append(buf+s,i-s+1);
                HTTPRequest req(m_logger,m_sender,inet_ntoa(m_addr.sin_addr),m_str);

                m_reqmanager->Push(req);
                m_str="";
                i+=2;
                s=i+1;
            }
        }
        m_str.append(buf+s,len-s);

        if(len < 256) {
            break;
        }
    }
}


std::string Reciever::GetIP() const {
    return  inet_ntoa(m_addr.sin_addr);
}
