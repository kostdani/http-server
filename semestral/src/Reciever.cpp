//
// Created by kostdani on 5/29/21.
//

#include "Reciever.h"


Reciever::Reciever(int descriptor,Queuer *q): Actor(descriptor) {
    m_q=q;
}

bool Reciever::multiplex(int epolld) {
    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLET;
    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}


void Reciever::onInput() {
    printf("recieve input %d\n",m_descriptor);
    char buf[256]{};
    while(true){
        int len = read(m_descriptor, buf, 256);
        printf("len %d\n",len);
        if(len==-1){
            printf("error %d\n",errno);
            break;
        }
        //std::cout.write(buf,len);
        Message *nm= new Message;
        *nm={Message::msg_type::BYTEARRAY,std::string(buf,len)};
        m_q->Push(nm);

        if(len < 256) {
            break;
        }
    }
}

void Reciever::onError() {
    printf("recieve error\n");
}

