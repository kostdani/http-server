//
// Created by kostdani on 6/12/21.
//

#include "HTTPServer.h"


HTTPServer::HTTPServer():m_epoller() {

}

bool HTTPServer::Start(int thrn) {
    m_stopper=new Counter();
    m_epoller.AddActor(m_stopper);

    m_logger=new Logger("serv.log");
    m_epoller.AddActor(m_logger);

    Accepter *ac=new Accepter(m_logger,"127.0.0.1",8080);
    m_epoller.AddActor(ac);

    m_stop=false;
    for (int i = 0; i < thrn; ++i) {
        m_threads.emplace_back(&HTTPServer::threadfunction,this);
    }
    return true;
}

bool HTTPServer::Stop() {
    if(!m_stop){
        m_stop= true;
        m_stopper->Add(1);
        for (auto & thr:m_threads)
            thr.join();
        return true;
    }
    return false;
}

void HTTPServer::threadfunction() {
    while (!m_stop){

        auto ev= m_epoller.getEvent();
        Actor *actor=(Actor *)ev.data.ptr;
        if((ev.events&EPOLLERR)||(ev.events&EPOLLHUP)||(ev.events&EPOLLRDHUP)){
            actor->onError();
        }else{
            if(ev.events&EPOLLIN)
                actor->onInput();
            if(ev.events&EPOLLOUT)
                actor->onOutput();

        }
    }
}