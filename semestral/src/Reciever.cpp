//
// Created by kostdani on 5/29/21.
//

#include "Reciever.h"


Reciever::Reciever(Logger *l, int descriptor, sockaddr_in addr, ContentGenerator *generator) : Actor(descriptor) {
    m_logger=l;
    m_reqmanager=generator;
    m_addr=addr;
}

bool Reciever::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLET;
    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}


void Reciever::onInput(int threadi) {
    if(!m_sender){
        m_sender=new Sender(dup(m_descriptor));
        AddActor(m_sender);
    }

    char buf[4096]{};
    while(true){
        int len = read(m_descriptor, buf, 256);
        if(len==-1){
            printf("error %d\n",errno);
            break;
        }
        int s=0;

        for (int i=s; i < len; ++i) {
            if(buf[i]=='\n'&& i+1<len && buf[i+1]=='\r'){
                m_str.append(buf+s,i-s+1);
                HTTPRequest req(m_logger,m_sender,m_str);
                req.m_log.host=inet_ntoa(m_addr.sin_addr);

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

void Reciever::onError(int threadi) {
    printf("recieve error\n");
}

std::string Reciever::GetIP() {
    return  inet_ntoa(m_addr.sin_addr);
}
